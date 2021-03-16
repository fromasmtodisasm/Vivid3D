from vivid import SceneNode
from vivid import VividComponent


class Test(SceneNode):
    def __init__(self,name="Antony",handle=0):
        self.name = name
        self.handle = handle        
        print("Test:",name)

    def DebugOne(self):
        print("Yeah:",self.name)

    def checkNum(self,val):
        print("Val:",val)


def createNode(name,handle):
    newNode = Test(name,handle)
    return newNode

def testNode(node):
    node.DebugOne()




