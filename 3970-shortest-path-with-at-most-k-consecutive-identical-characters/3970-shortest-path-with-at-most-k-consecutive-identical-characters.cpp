class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        // Adjacency list: u -> list of pairs (v, w)
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }
        
        // Priority queue stores: {weight_sum, node, count}
        // We want a min-heap, so we use greater or custom comparator
        priority_queue<tuple<long long, int, int>, 
                       vector<tuple<long long, int, int>>, 
                       greater<tuple<long long, int, int>>> pq;
        
        // dist[u][count] stores the minimum weight to reach node u with a given consecutive count
        // Since count can range from 1 to k, we use size (k + 1)
        vector<vector<long long>> dist(n, vector<long long>(k + 1, -1));
        
        // Start at node 0. 
        // Note: Depending on whether the starting node counts toward the label sequence, 
        // its initial count is 1.
        int start_count = 1;
        pq.push({0, 0, start_count});
        dist[0][start_count] = 0;
        
        while (!pq.empty()) {
            auto [w, u, count] = pq.top();
            pq.pop();
            
            // If we reached the target node, since it's Dijkstra, the first time we pop n - 1 is optimal
            if (u == n - 1) {
                return w;
            }
            
            if (w > dist[u][count]) continue;
            
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                int next_count = (labels[v] == labels[u]) ? count + 1 : 1;
                
                // If the consecutive identical characters exceed k, skip this transition
                if (next_count > k) continue;
                
                long long next_w = w + weight;
                
                if (dist[v][next_count] == -1 || next_w < dist[v][next_count]) {
                    dist[v][next_count] = next_w;
                    pq.push({next_w, v, next_count});
                }
            }
        }
        
        return -1;
    }
};