class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival,
                               vector<int>& load) {

        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {completion time, server ID}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        vector<int> count(k, 0);

        int n = arrival.size();

        for (int i = 0; i < n; i++) {

            // 1. Free all servers whose requests have completed
            while (!busy.empty() &&
                   busy.top().first <= arrival[i]) {

                int server = busy.top().second;

                available.insert(server);
                busy.pop();
            }

            // 2. If all servers are busy, drop the request
            if (available.empty()) {
                continue;
            }

            // 3. Find the preferred server or next available one
            int preferred = i % k;

            auto it = available.lower_bound(preferred);

            // 4. Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // 5. Assign the request
            available.erase(it);

            count[server]++;

            // 6. Store its completion time
            busy.push({
                (long long)arrival[i] + load[i],
                server
            });
        }

        // 7. Find maximum number of requests handled
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};