#include "p_gen.h"

#include <ctime>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

struct tile map[MAP_HEIGHT][MAP_WIDTH];

std::pair<int, int> region_coords[64];
int region_counter = 0;

int seed = time(NULL);
int alive_prob = 58;
int generations = 8;

// Minimum number of walkable tiles a cave region must contain.
// Smaller disconnected regions are converted into walls.
int min_pocket_size = 15;

void gen_cave() {
    srand(seed);

    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            if (rand() % 100 > alive_prob)
                map[h][w].state = DEAD;
        }
    }
}

int near(int x, int y) {
    int count = 0;

    for (int h = y - 1; h < 2 + y; h++) {
        for (int w = x - 1; w < 2 + x; w++) {
            if (!(w == x && h == y))
                count += map[h][w].state;
        }
    }

    return count;
}

void pocket_remover() {
    // Clear the visited marks from any previous search.
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            map[h][w].visited = 0;
        }
    }

    // Four-direction movement: up, down, left, right.
    int dh[] = { -1, 1, 0, 0 };
    int dw[] = { 0, 0, -1, 1 };

    // Search the interior of the map for each disconnected floor region.
    for (int h = 1; h < MAP_HEIGHT - 1; h++) {
        for (int w = 1; w < MAP_WIDTH - 1; w++) {
            // Skip walls and floor tiles already included in a region.
            if (map[h][w].state != DEAD || map[h][w].visited)
                continue;

            std::queue<std::pair<int, int>> q;
            std::vector<std::pair<int, int>> region;

            q.push({ h, w });
            map[h][w].visited = 1;

            while (!q.empty()) {
                auto [ch, cw] = q.front();
                q.pop();

                // Remember this tile so we can remove the whole region if it is small.
                region.push_back({ ch, cw });

                for (int i = 0; i < 4; i++) {
                    int nh = ch + dh[i];
                    int nw = cw + dw[i];

                    // Keep the search inside the map's interior.
                    if (nh < 1 || nh >= MAP_HEIGHT - 1 ||
                        nw < 1 || nw >= MAP_WIDTH - 1)
                        continue;

                    if (map[nh][nw].state == ALIVE &&
                        !map[nh][nw].visited) {
                        map[nh][nw].visited = 1;
                        q.push({ nh, nw });
                    }
                }
            }

            // If this connected floor region is too small, turn it into walls.
            if (region.size() < static_cast<std::size_t>(min_pocket_size)) {
                for (const auto& position : region) {
                    int rh = position.first;
                    int rw = position.second;
                    map[rh][rw].state = DEAD;
                }
            }

            if (region.size() >= static_cast<std::size_t>(min_pocket_size)) {
                int index = rand() % region.size();
                region_coords[region_counter] = region[index];
                region_counter++;
            }
        }
    }
}

void tunnel_carver() {
    for (int i = 0; i < region_counter - 1; i++) {
        int h = region_coords[i].first;
        int w = region_coords[i].second;
        int diff_h = region_coords[i + 1].first - h;
        int diff_w = region_coords[i + 1].second - w;

        while (diff_h != 0 || diff_w != 0) {
            bool move_vert;

            if (diff_w == 0) move_vert = true;
            else if (diff_h == 0) move_vert = false;
            else move_vert = rand() % 2;

            if (move_vert) {
                if (diff_h < 0) {
                    h--;
                    diff_h++;
                }
                else {
                    h++;
                    diff_h--;
                }
            }
            else {
                if (diff_w < 0) {
                    w--;
                    diff_w++;
                }
                else {
                    w++;
                    diff_w--;
                }
            }
            map[h][w].state = ALIVE;
        }
    }
}

void gen_map() {
    gen_cave();

    for (int gen = 0; gen < generations; gen++) {
        for (int h = 1; h < MAP_HEIGHT - 1; h++) {
            for (int w = 1; w < MAP_WIDTH - 1; w++) {
                int count = near(w, h);

                if (map[h][w].state == DEAD && count >= 6)
                    map[h][w].state = ALIVE;

                if (map[h][w].state == ALIVE && count <= 3)
                    map[h][w].state = DEAD;
            }
        }
    }

    // Remove small disconnected walkable regions after cave generation.
    pocket_remover();
    tunnel_carver();
}
