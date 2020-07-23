class Circle:
    def __init__(self, name, x, y, rad, orientation):
        self.name = name
        self.x = x
        self.y = y
        self.rad = rad
        self.orientation = orientation

class CVXGeo:
    def __init__(self):
        self.num = 0
        self.circles = []
        self.implications = []
        self.orientation = str()

    def normalize(self):
        # get bounding box
        min_x = 0
        min_y = 0
        max_x = 0
        max_y = 0
        for ind, circ in enumerate(self.circles):
            if ind == 0:
                min_x = circ.x
                max_x = circ.x
                min_y = circ.y
                max_y = circ.y
            if min_x > circ.x:
                min_x = circ.x
            if max_x < circ.x:
                max_x = circ.x
            if min_y > circ.y:
                min_y = circ.y
            if max_y < circ.y:
                max_y = circ.y
        # calculate factor to scale by
        OUT_DIM = 5 # fit output into 10 x 10 square
        scale_factor = 0
        if (max_x - min_x) < (max_y - min_y):
            scale_factor = OUT_DIM / (max_y - min_y)
        else:
            scale_factor = OUT_DIM / (max_x - min_x)
        # translate and scale
        for ind, circ in enumerate(self.circles):
            self.circles[ind].x -= min_x
            self.circles[ind].x *= scale_factor
            self.circles[ind].y -= min_y
            self.circles[ind].y *= scale_factor
            self.circles[ind].rad *= scale_factor 

    def get_fields(self):
        filename = str(input("filename:"))
        f  = open(filename + ".txt", "r") 
        self.num = int(f.readline())
        for name in ["a", "b", "c", "d", "e"]:
            #for name in ["a", "b"]:
            x = float(f.readline())
            y = float(f.readline())
            radius = float(f.readline())
            orientation = str(f.readline().rstrip())
            self.circles.append(Circle(name, x, y, radius, orientation))
        imp = f.readline()
        imp = imp.rstrip('\n')
        while " " in imp:
            pair = imp.split(" ")
            self.implications.append(pair[0:2])
            imp = f.readline()
        f.close()
    def pretty_print(self):
        print("")
        tab_space = 4 * " "
        print("\\section*{%d}"%(self.num))
        print("\\begin{figure}[H]\n"\
              + tab_space + "\\centering\n"\
              + (2 * tab_space) + "\\begin{tikzpicture}")
        for circ in self.circles:
            if circ.rad > 0.01:
                print((3 * tab_space) + "\\draw (%.4f,%.4f) circle[radius=%.4f];"%(circ.x, circ.y, circ.rad))
                if circ.orientation == "n":
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.001] node[anchor=north] {$%s$};" %(circ.x, circ.y-circ.rad, circ.name))
                elif circ.orientation == "s":
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.001] node[anchor=south] {$%s$};" %(circ.x, circ.y+circ.rad, circ.name))
                elif circ.orientation == "e":
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.001] node[anchor=east] {$%s$};" %(circ.x-circ.rad, circ.y, circ.name))
                else:
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.001] node[anchor=west] {$%s$};" %(circ.x+circ.rad, circ.y, circ.name))
            else:
                if circ.orientation == "n":
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.075] node[anchor=north] {$%s$};" %(circ.x, circ.y, circ.name))
                elif circ.orientation == "s":
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.075] node[anchor=south] {$%s$};" %(circ.x, circ.y+circ.rad, circ.name))
                elif circ.orientation == "e":
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.075] node[anchor=east] {$%s$};" %(circ.x-circ.rad, circ.y, circ.name))
                else:
                    print((3 * tab_space) + "\\filldraw [gray] (%.4f,%.4f) circle[radius=0.075] node[anchor=west] {$%s$};" %(circ.x+circ.rad, circ.y, circ.name))
        imp_str = ""
        for imp in self.implications[:-1]:
            imp_str += "$%s \\rightarrow %s$, "%(imp[0], imp[1])
        if len(self.implications) > 0:
            imp = self.implications[-1]
            imp_str += "$%s \\rightarrow %s$"%(imp[0], imp[1])
        print((2 * tab_space) + "\\end{tikzpicture}\n"\
            + tab_space + "\\caption{%s}\n"\
            "\\end{figure}"%(imp_str))

cg = CVXGeo()
cg.get_fields()
#cg.circles = [Circle("a", 1.02, 3.5, 0.7), Circle("b", 2.3, 5.02, 0.98),
#        Circle("c", 3.0, 5, 0.001)]
cg.normalize()
cg.pretty_print()
