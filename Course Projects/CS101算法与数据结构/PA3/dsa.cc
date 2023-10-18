#pragma once

#include "dsa.h"

#include <queue>

Graph::Graph(VertexId vertices, std::vector<Edge> edges)
    : vertices(vertices), adj(vertices + 1) {
  for (auto e : edges) adj[e.u].push_back(e);
}

void Graph::sssp(VertexId src, std::vector<Weight> &dis) {
std::priority_queue<std::pair<Weight, VertexId>> pq;
  std::vector<bool> vis(vertices + 1);
  dis.resize(vertices + 1);
  std::fill(dis.begin(), dis.end(), INF);
  dis[src] = 0;
  pq.push({0, src});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto e : adj[u]) {
      if (dis[e.v] > dis[u] + e.w) {
        dis[e.v] = dis[u] + e.w;
        pq.push({-dis[e.v], e.v});
      }
    }
  }
}

void Graph::mst(VertexId src, std::vector<Edge> &mst_edges) {
  // Use Prim's algorithm to find a minimum spanning tree of the graph,starting from `src`.
  // implement an MST algorithm with O((V+E)\log (V+E))O((V+E)log(V+E)) running time
  std::vector<int> vis(vertices + 3);
  std::priority_queue<std::pair<Weight, VertexId>> pq;
  vis[src] = 1;
  for (auto e : adj[src]) pq.push({-e.w, e.v});
  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    mst_edges.push_back({src, u, -w});
    for (auto e : adj[u]) pq.push({-e.w, e.v});
  }
  
}