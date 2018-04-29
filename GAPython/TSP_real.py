import copy
import random


INFINITY = 99999.99

def generate_table(coordinates):
    n = len(coordinates)
    distances = [[INFINITY for i in range(n)] for i in range(n)]
    for i in range(n):
        for j in range(i, n):
            d = distance(coordinates[i], coordinates[j])
            distances[i][j] = d
            distances[j][i] = d
    return distances

def distance(c1, c2):
    return round(float(((c1[0] - c2[0]) ** 2 + (c1[1] - c2[1]) ** 2) ** 0.5), 2)

def tsp(data):
    n = len(data)
    dist = generate_table(data)
    length = 0
    path = []
    start = random.randrange(n)
    first_vertex = copy.deepcopy(dist[start])
    for i in range(n):
        next = dist[start].index(min(dist[start]))
        length += dist[start][next]
        path.append(next)
        for i in range(n):
            dist[i][next] = INFINITY
        start = next
    print(first_vertex[path[-1]])
    length += first_vertex[path[-1]]
    path.append(path[0])
    print(length, path)
    print(sorted(path))
    return path, length



def description():
    return "This program uses nearest neighbours algorithm to find the closest root between cities." \
        "Firstly, it creates a table of all the distances between cities, and fills distance of a city to itself as an INFINITY" \
        "(a very large number). Then, it picks a random vertex to start with. The program calcualtes the closest city by finding " \
        "a minimal distance out of all. After vertex has been visited all the distances to that city are set to INFINITY, so" \
        "it is never visited again. After visiting all the cities it finds a way to first city and returns the length and a sequence " \
        "of visited."






tsp([[1380, 939], [2848, 96], [3510, 1671], [457, 334], [3888, 666], [984, 965], [2721, 1482], [1286, 525], [2716, 1432], [738, 1325], [1251, 1832], [2728, 1698], [3815, 169], [3683, 1533], [1247, 1945], [123, 862], [1234, 1946], [252, 1240], [611, 673], [2576, 1676], [928, 1700], [53, 857], [1807, 1711], [274, 1420], [2574, 946], [178, 24], [2678, 1825], [1795, 962], [3384, 1498], [3520, 1079], [1256, 61], [1424, 1728], [3913, 192], [3085, 1528], [2573, 1969], [463, 1670], [3875, 598], [298, 1513], [3479, 821], [2542, 236], [3955, 1743], [1323, 280], [3447, 1830], [2936, 337], [1621, 1830], [3373, 1646], [1393, 1368], [3874, 1318], [938, 955], [3022, 474], [2482, 1183], [3854, 923], [376, 825], [2519, 135], [2945, 1622], [953, 268], [2628, 1479], [2097, 981], [890, 1846], [2139, 1806], [2421, 1007], [2290, 1810], [1115, 1052], [2588, 302], [327, 265], [241, 341], [1917, 687], [2991, 792], [2573, 599], [19, 674], [3911, 1673], [872, 1559], [2863, 558], [929, 1766], [839, 620], [3893, 102], [2178, 1619], [3822, 899], [378, 1048], [1178, 100], [2599, 901], [3416, 143], [2961, 1605], [611, 1384], [3113, 885], [2597, 1830], [2586, 1286], [161, 906], [1429, 134], [742, 1025], [1625, 1651], [1187, 706], [1787, 1009], [22, 987], [3640, 43], [3756, 882], [776, 392], [1724, 1642], [198, 1810], [3950, 1558], [3477, 949], [91, 1732], [3972, 329], [198, 1632], [1806, 733], [538, 1023], [3430, 1088], [2186, 766], [1513, 1646], [2143, 1611], [53, 1657], [3404, 1307], [1034, 1344], [2823, 376], [3104, 1931], [3232, 324], [2790, 1457], [374, 9], [741, 146], [3083, 1938], [3502, 1067], [1280, 237], [3326, 1846], [217, 38], [2503, 1172], [3527, 41], [739, 1850], [3548, 1999], [48, 154], [1419, 872], [1689, 1223], [3468, 1404], [1628, 253], [382, 872], [3029, 1242], [3646, 1758], [285, 1029], [1782, 93], [1067, 371], [2849, 1214], [920, 1835], [1741, 712], [876, 220], [2753, 283], [2609, 1286], [3941, 258], [3613, 523], [1754, 559], [2916, 1724], [2445, 1820]])