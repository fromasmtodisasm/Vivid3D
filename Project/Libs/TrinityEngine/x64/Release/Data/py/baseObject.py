class Vividobject:
    'Common base class for python side of Vivid3D'
    objCount = 0

    def __init__(self,name):
        self.name = name
        vividobject.objCount+=1

    def displayDebug(self):
        print("VividName:",self.name)
    


