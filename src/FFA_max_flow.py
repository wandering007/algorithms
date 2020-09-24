# The Ford–Fulkerson method or Ford–Fulkerson algorithm (FFA) is
# an algorithm that computes the maximum flow in a flow network.
# In the case that the algorithm runs forever, the flow might not
# even converge towards the maximum flow. However, this situation
# only occurs with irrational flow values. When the capacities are
# integers, the runtime of Ford–Fulkerson is bounded by O(Ef), 
# where E is the number of edges in the graph and f is the maximum flow in the graph. 
# https://en.wikipedia.org/wiki/Ford–Fulkerson_algorithm

class Edge(object):
	def __init__(self, u, v, w):
		self.source = u
		self.sink = v
		self.capacity = w
	def __repr__(self):
		return "%s->%s:%s" % (self.source, self.sink, self.capacity)

class FlowNetwork(object):
	def __init__(self):
		self.adj = {}
		self.flow = {}

	def add_vertex(self, vertex):
		self.adj[vertex] = []

	def get_edges(self, v):
		return self.adj[v]

	def add_edge(self, u, v, w = 0):
		if u == v:
			raise ValueError("u == v")
		edge = Edge(u, v, w)
		redge = Edge(v, u, 0)
		edge.redge = redge
		redge.redge = edge
		self.adj[u].append(edge)
		self.adj[v].append(redge)
		self.flow[edge] = 0
		self.flow[redge] = 0

	def find_path(self, source, sink, path):
		if source == sink:
			return path
		for edge in self.get_edges(source):
			residual = edge.capacity - self.flow[edge]
			if residual > 0 and edge not in path:
				result = self.find_path(edge.sink, sink, path + [edge])
				if result != None:
					return result

	def  max_flow(self, source, sink):
		path = self.find_path(source, sink, [])
		while path != None:
			residuals = [edge.capacity - self.flow[edge] for edge in path]
			flow = min(residuals)
			for edge in path:
				self.flow[edge] += flow
				self.flow[edge.redge] -= flow
			path = self.find_path(source, sink, [])
		return sum(self.flow[edge] for edge in self.get_edges(source))