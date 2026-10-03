#User function Template for python3

class Solution:
    def shortestDistance(self,N,M,A,X,Y):
        #code here

        direcciones = [(-1,0),(1,0),(0,-1),(0,1)] # up, down left, right

        queue = [[0,0,0]] # i,j,conteo

        visitados = [(0,0)]

        size_queue = 1
        
        if A[0][0]==1 and (X,Y)==(0,0):
            return 0
        elif A[0][0]==0:
            return -1

        while size_queue!=0:

            actual = queue.pop(0)
            size_queue-=1
    
            up = actual[0]+direcciones[0][0]
            down = actual[0]+direcciones[1][0]
            left = actual[1]+direcciones[2][1]
            right = actual[1]+direcciones[3][1]
    
            if up >=  0 and (up,actual[1]) not in visitados and A[up][actual[1]]==1:
                if (up, actual[1]) == (X,Y):
                    return actual[2]+1
                else:
                    visitados.append((up, actual[1]))
                    queue.append([up, actual[1],actual[2]+1])
                    size_queue+=1
    
            if down < N and (down,actual[1]) not in visitados and A[down][actual[1]]==1 :
                if (down, actual[1]) == (X,Y):
                    return actual[2]+1
                else:
                    visitados.append((down, actual[1]))
                    queue.append([down, actual[1],actual[2]+1])
                    size_queue+=1
    
            if left >= 0 and (actual[0],left) not in visitados and A[actual[0]][left]==1:
                if (actual[0],left) == (X,Y):
                    return actual[2]+1
                else:
                    visitados.append((actual[0],left))
                    queue.append([actual[0],left,actual[2]+1])
                    size_queue+=1
    
            if right < M and (actual[0],right) not in visitados and A[actual[0]][right]==1 :
                if (actual[0],right) == (X,Y):
                    return actual[2]+1
                else:
                    visitados.append((actual[0],right))
                    queue.append([actual[0],right,actual[2]+1])
                    size_queue+=1

        return -1