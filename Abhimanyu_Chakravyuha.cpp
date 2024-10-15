#include <bits/stdc++.h>

using namespace std;

const int total_enemies = 11; // Total number of enemies Abhimanyu must face

int initial_energy;  // Starting energy of Abhimanyu

// Function to determine if Abhimanyu can overcome the Chakravyuha challenge
bool canAbhimanyuWin(vector<int>& enemy_strength, int current_enemy, int current_energy, int attack_from_back, int skip_count, int recharge_count)
{
    // Base case: Abhimanyu has defeated all enemies
    if (current_enemy == total_enemies)
        return true;

    bool success = false;

    // Option 1: Recharge Abhimanyu if possible
    if (recharge_count > 0 && current_energy < initial_energy)
        success |= canAbhimanyuWin(enemy_strength, current_enemy, initial_energy, attack_from_back, skip_count, recharge_count - 1);

    // Deal with an attack from behind if it exists
    if (current_energy >= attack_from_back)
    {
        current_energy -= attack_from_back;
        attack_from_back = 0;
    }
    else
        return false;

    // Option 2: Skip the current enemy if allowed
    if (skip_count > 0)
        success |= canAbhimanyuWin(enemy_strength, current_enemy + 1, current_energy, attack_from_back, skip_count - 1, recharge_count);

    // Option 3: Fight the current enemy without using skips or recharge

    if (current_energy >= enemy_strength[current_enemy])
    {
        if (current_enemy == 2 || current_enemy == 6)
            attack_from_back = enemy_strength[current_enemy] / 2;

        success |= canAbhimanyuWin(enemy_strength, current_enemy + 1, current_energy - enemy_strength[current_enemy], attack_from_back, skip_count, recharge_count);
    }

    return success;
}

int main()
{
    vector<int> enemy_strength(total_enemies); // Stores the strength of enemies from 1 to 11

    for (int i = 0; i < total_enemies; i++)
        cin >> enemy_strength[i];

    int skips, recharges; // skips: Total number of skips, recharges: Total number of recharges
    cin >> initial_energy >> skips >> recharges;
    skips = min(skips, total_enemies);  // Ensure skips are within bounds
    recharges = min(recharges, total_enemies); // Ensure recharges are within bounds

    int back_attack = 0; // Keeps track of enemies attacking from behind

    if (canAbhimanyuWin(enemy_strength, 0, initial_energy, back_attack, skips, recharges))
        cout << "Abhimanyu can cross the Chakravyuha" << endl;
    else
        cout << "Abhimanyu cannot cross the Chakravyuha" << endl;

    return 0;
}

// Test case 1:

// total_enemies = 11
// enemy_strength = {0, 15, 11, 6, 7, 3, 5, 12, 8, 10, 1}
// initial_energy = 13
// skips = 6
// recharges = 2
// Expected output: Abhimanyu can cross the Chakravyuha

// Test case 2:

// total_enemies = 11
// enemy_strength = {0, 15, 11, 6, 7, 3, 5, 12, 8, 10, 1}
// initial_energy = 5
// skips = 5
// recharges = 3
// Expected output: Abhimanyu cannot cross the Chakravyuha
