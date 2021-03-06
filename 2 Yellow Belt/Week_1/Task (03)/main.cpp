#include <cstdint>
#include <iostream>

using namespace std;

int main() {
    int N, R;
    cin >> N >> R;
    uint64_t answer = 0;
    for (int i = 0; i < N; ++i) {
        int W, H, D;
        cin >> W >> H >> D;
        answer += static_cast<uint64_t>(W) * H * D;
    }
    answer *= R;
    cout << answer << endl;
    return 0;
}