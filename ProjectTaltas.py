#Project for Combinatorics 
#Written by Camille Taltas

#Imports for Visualizing Functions
import numpy as np
import networkx as nx
import matplotlib as plt
plt.rcParams['figure.figsize'] = [12.0,12.0]
def grid_positions(G,scale=1):
    return dict((n,(scale*n[0],scale*n[1])) for n in G.nodes())
    
def edge_subgraph_nodes(E):
    V = set()
    for e in E:
        V.update(e)
        
    return V
    
def set_node_colors(G,N,color):
    for n in N:
        G.node[n]['color'] = color
        
def set_edge_colors(G,E,color):
    for i,j in E:
        G[i][j]['color'] = color
        
def set_edge_weights(G,E,weight):
    for i,j in E:
        G[i][j]['weight'] = weight
        
def draw_grid(n,X):
    
    #Draw an n x n grid with edges / nodes from X in red
    
    
    G = nx.grid_2d_graph(n+1,n+1)
    set_node_colors(G,G.nodes(),'k')
    set_edge_colors(G,G.edges(),'k')
    set_edge_weights(G,G.edges(),0.5)
    
    set_node_colors(G,edge_subgraph_nodes(X),'r')
    set_edge_colors(G,X,'r')
    set_edge_weights(G,X,1)
    
    nc = [G.node[n]['color'] for n in G.nodes()]
    ec = [G[i][j]['color'] for i,j in G.edges()]
    w = [G[i][j]['weight'] for i,j in G.edges()]
    
    nx.draw(G,grid_positions(G,2),node_size=0.5,width=w,node_color=nc,edge_color=ec)

def flatten(l):
    return [x for y in l for x in y]

#Exercise 1
#Output vertex set by creating a list of pairs representing all subsets of size 2 of V = {0,1,..,n}
def  grid_vertices(n):
    E = []
    for i in xrange(0,n+1):
        for j in xrange(0,n+1):
            E.append((i,j))
    return E

#Exercise 2 
#Output the edge representing a step to the right 
def step_right(v):
    v_right=(v[0]+1,v[1])
    edge = [v,v_right]
    return edge

#Exercise 3
#Output the edge representing a step to up 
def step_up(v):
    v_right=(v[0],v[1]+1)
    edge = [v,v_right]
    return edge

#Exercise 4 
#Output the path determined by a list of 0s and 1s representing stepping up or to the right, respectively. 
def set_to_path(s):
    path = []
    pair = (0,0)
    for i in s:
        if i == 1:
            move = step_right(pair)
            path.append(move)
        else:
            move = step_up(pair)
            path.append(move)
        pair = move[1]   
    return path
#Exercise 5 
#Output a list of size n which contains integers picked at random and uniformly between 0 and 1, 
def uniform_set(n):
    set_array = np.random.randint(2,size=n)
    set_list = list(set_array)
    return set_list

#Exercise 6 
# Create a list of size n with n-k 0s and k 1s picked at random and uniformly. 
def uniform_k_set(n,k):
    uni_set = []
    for i in xrange (0,k):
        uni_set.append(1)
    for j in xrange (0,n-k):
        uni_set.append(0)
        np.random.shuffle(uni_set)
    return uni_set

#Exercise 7 
#Create a list of size m where each element is a list of size n with elements chosen between 0 and 1 uniformly
def uniform_sets(m,n):
    sets = []
    for i in xrange (0,m):
        sets.append(uniform_set(n))
    return sets

#Exercise 8
#Create a function that inputs a list of sets and outputs a list representing paths created by each of these sets 
def sets_to_paths(sets_list):
    paths = []
    for i in sets_list:
        paths.append(set_to_path(i))
    return paths

#Exercise 9 
#Initiating 10 000 uniform sets of size 100 
u10k = uniform_sets(10000,100)
#Conversion to paths
up10k = sets_to_paths(u10k)
#Draw Grid
draw_grid(100, flatten(up10k))

#Exercise 10 
#Output a list of m uniform_k_sets as defined in exercise 6
def uniform_k_sets(m,n,k):
    sets = []
    for i in xrange(0,m):
        sets.append(uniform_k_set(n,k))
    return sets 

#Exercise 11 
#Initiate 10 000 subets of size 200 with 100 0s ans 1s 
h10k = uniform_k_sets(10000, 200, 100)
#Conversion to paths 
hp10k = sets_to_paths(h10k)
#Draw Grid
draw_grid(100, flatten(hp10k))

#Exercise 12
#Prints out the maximum distance from the diagonal any path in up10k reaches 
max = 0
#Loop over the paths 
for i in up10k:
    reaching_vertex = i[99][1]
#Find the maximum distance and print it out.
    if abs(reaching_vertex[0]-reaching_vertex[1])>max:
        max = abs(reaching_vertex[0]-reaching_vertex[1])
print 'The max distance from the diagonal reached is ', max

#Here, the distance reached at the end of every path is equal to the absolute difference in the number of 0s and 1s. 
#Since the choice of 0 or 1 is made with a probability of 1/2 independently, we expect to have around 50 1s and 50 0s.
#Hence, it would be expected that every path reaches a distance close to zero by the end. 
#However, the maximum distance found does not show the following.

#Prints the number of paths in hp10k that never go below the diagonal.
count_paths = 0
#Loop over the paths 
for i in hp10k:
    count_below = 0
#Loop over the edges. Count if any of the second vertices go below the diagonal, which suffices to test all possible vertices in each paths.
    for j in i:
        if j[1][0]>j[1][1]:
            count_below = count_below +1 
#If the total count of vertices below the diagonal is zero, count this path. 
    if count_below == 0:
        count_paths = count_paths +1 
print 'The number of paths that do not go below the diagonal are ', count_paths

#Here we can compare a vertex being below a diagonal to a balanced word of length 200. 
#As long as there are no more 1s than 0s in the set, no vertices will be below the diagonal in the path. 
# 1/101 * (200 choose 100) is the number of balanced words one might expect to find. 
# With 100 0s and 100 1s, we have 200 choose 100 ways of ordering these sets.
#Hence the number of sets total divided by 101 will give the expected number of balanced sets. 
balanced = 1.0/101.0 * 10000.0 
print 'We expected ', balanced, ' numbers of paths to not go below the diagonal.'

