RESET = "\033[0m"
RED = "\033[31m"
GREEN =	"\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"

def parse(data, port, origin):
    if origin == "server":
        print (BLUE, "[", origin, ":", str(port), "]", data, RESET)
    else:
        print (GREEN, "[", origin, ":", str(port), "]", data, RESET)

# print (":".join("{:02x}".format(ord(c)) for c in data))
#il y a un lf ( + un cr) en fin de data, ducoup c'est pour ca que ca print sur 2 lignes, faites un bail du genre pour print sur 1:
#print ("[" + origin + ":" + str(port) + "]" + data, end='') je c meme pas si ca marche mais c'est un bail du genre pour sur

# HOW TO PRINT
#print content, with variable substitution
# print ("content {}".format(variable))

#print combination of variables and strings, single space added automatically
# print ("content", variable, "other content")