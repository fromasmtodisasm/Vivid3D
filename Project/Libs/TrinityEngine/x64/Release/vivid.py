from vividobject import Vividobject

class SceneNode(Vividobject):
    def __init__(self,handle,name):
        self.name = name
    
class VividComponent:
    def __init__(self,node):
        self.node = node

    def Init(self):
        print("Initialized.")

    def Start(self):
        print("Started")

    def Stop(self):
        print("Stopped")

    def Pause(self):
        print("Paused")

    def Update(self):
        print("Updated")

    def Render(self):
        print("Rendered")

        
def NewNode(handle,name):
    nn = SceneNode(handle,name)
    return nn

print("Imported Vivid!")


#t1 = Vividobject("Antony")

#t1.displayDebug()
