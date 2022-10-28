```mermaid
classDiagram
    class GeometryLib {

    }

    class Point3d {
        +double x
        +double y
        +double z

        +operator+()
        +operator-()
        +operator*()
        +operator/()
    }
    GeometryLib o-- Point3d

    class Vector3d {
        +double x
        +double y
        +double z

        +Normalize()
        Length(): double
        Inner(Vector3d vector): double
        Cross(Vector3d vector): Vector3d

        +operator+()
        +operator-()
        +operator*()
        +operator/()
    }
    GeometryLib o-- Vector3d

    class alias {
        +PointSet
        +PointVectorSet
    }
    GeometryLib o-- alias

	class MapLib {
		+ReadCSV(string path): Map2d[double]
		+WriteCSV(string path, Map2d[double] map)
	}

    class Map2d {
        +int x
        +int y
        +int width
        +int height
        +vector[vector[T]] data
    }
    MapLib o-- Map2d

    class Neighbor {
        +double[3][3] data
    }
    MapLib o-- Neighbor

    class Filter {
        +Calculate(Neighbor neighbor): double
    }
    MapLib <.. Filter

    class Judge{
        +double simulator_threshold
        +double separator_threshold

        +Separate(Map2d[(double, double)] map): (Map2d[double], Map2d[double])
        +Simulate(double value, Neighbor neighbor): Neighbor
    }
    MapLib <.. Judge

    class Reducer{
        +double searcher_threshold
        
        +GetNormalVectorIn(Neighbor neighbor): Vector3d
        +SearchPointGroups(Map2d[(double, Vector3d)] map): vector[PointVectorSet]
    }
    GeometryLib <.. Reducer
    MapLib <.. Reducer

    class Face {
        -Point3d _origin
        -Vector3d _normal
        -PointSet _points

        +points(): PointSet
        +Face(PointVectorSet set)
        +DeleteInsidePoints()
        +ProjectPoints()
    }
    Reducer o-- Face

    class DelaunayLib {
        +MakePolygon(PointSet points): vector[(int, int, int)]
        +MakeBigTriangle(PointSet points)
        +Randomize(PointSet points): PointSet
    }
    GeometryLib <.. DelaunayLib

    class Triangle {
        +vector[Point3d]* points
        +int[3] point_indices
        +Triangle*[3] children
        +Triangle*[3] neighbors

        +Contains(Point3d point): bool
        +FindDeepest(Point3d point): Triangle
        +Divide(Point3d point)
        +Flip()
    }
    DelaunayLib o-- Triangle

    class Converter {
        +MakeGroundPoints(Map2d[double] map): Map2d[double]
        +WriteWRL(string path, PointSet points, vector[(int, int, int)] indexSet)
    }
    MapLib <.. Converter
    DelaunayLiv <.. Converter
```