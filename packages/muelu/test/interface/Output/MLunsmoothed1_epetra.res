========================= Aggregate option summary  =========================
min Nodes per aggregate :               1
min # of root nbrs already aggregated : 0
aggregate ordering :                    natural
=============================================================================
Level 0
 Setup Smoother (MueLu::IfpackSmoother{type = point relaxation stand-alone})
 relaxation: type = symmetric Gauss-Seidel   [unused]
 relaxation: sweeps = 2   [unused]
 relaxation: damping factor = 1   [unused]

Level 1
 Build (MueLu::TentativePFactory)
  Build (MueLu::UncoupledAggregationFactory)
   Build (MueLu::CoalesceDropFactory)
    Build (MueLu::AmalgamationFactory)
    [empty list]

   aggregation: drop tol = 0   [default]
   aggregation: Dirichlet threshold = 0   [default]
   aggregation: drop scheme = classical   [default]
   lightweight wrap = 0   [default]

  aggregation: mode = old   [default]
  aggregation: max agg size = -1   [default]
  aggregation: min agg size = 1   [unused]
  aggregation: max selected neighbors = 0   [unused]
  aggregation: ordering = natural   [unused]
  aggregation: enable phase 1 = 1   [default]
  aggregation: enable phase 2a = 1   [default]
  aggregation: enable phase 2b = 1   [default]
  aggregation: enable phase 3 = 1   [default]
  aggregation: preserve Dirichlet points = 0   [default]
  UseOnePtAggregationAlgorithm = 0   [default]
  UsePreserveDirichletAggregationAlgorithm = 0   [unused]
  UseUncoupledAggregationAlgorithm = 1   [default]
  UseMaxLinkAggregationAlgorithm = 1   [default]
  UseIsolatedNodeAggregationAlgorithm = 1   [default]
  UseEmergencyAggregationAlgorithm = 1   [default]
  OnePt aggregate map name =    [default]

  Build (MueLu::CoarseMapFactory)
  Striding info = {}   [default]
  Strided block id = -1   [default]
  Domain GID offsets = {0}   [default]

 [empty list]

 Transpose P (MueLu::TransPFactory)
 [empty list]

 Computing Ac (MueLu::RAPFactory)
 transpose: use implicit = 0   [default]
 Keep AP Pattern = 0   [default]
 Keep RAP Pattern = 0   [default]
 CheckMainDiagonal = 0   [default]
 RepairMainDiagonal = 0

 Setup Smoother (MueLu::IfpackSmoother{type = point relaxation stand-alone})
 relaxation: type = symmetric Gauss-Seidel   [unused]
 relaxation: sweeps = 2   [unused]
 relaxation: damping factor = 1   [unused]

Level 2
 Build (MueLu::TentativePFactory)
  Build (MueLu::UncoupledAggregationFactory)
   Build (MueLu::CoalesceDropFactory)
    Build (MueLu::AmalgamationFactory)
    [empty list]

   aggregation: drop tol = 0   [default]
   aggregation: Dirichlet threshold = 0   [default]
   aggregation: drop scheme = classical   [default]
   lightweight wrap = 0   [default]

  aggregation: mode = old   [default]
  aggregation: max agg size = -1   [default]
  aggregation: min agg size = 1   [unused]
  aggregation: max selected neighbors = 0   [unused]
  aggregation: ordering = natural   [unused]
  aggregation: enable phase 1 = 1   [default]
  aggregation: enable phase 2a = 1   [default]
  aggregation: enable phase 2b = 1   [default]
  aggregation: enable phase 3 = 1   [default]
  aggregation: preserve Dirichlet points = 0   [default]
  UseOnePtAggregationAlgorithm = 0   [default]
  UsePreserveDirichletAggregationAlgorithm = 0   [unused]
  UseUncoupledAggregationAlgorithm = 1   [default]
  UseMaxLinkAggregationAlgorithm = 1   [default]
  UseIsolatedNodeAggregationAlgorithm = 1   [default]
  UseEmergencyAggregationAlgorithm = 1   [default]
  OnePt aggregate map name =    [default]

  Nullspace factory (MueLu::NullspaceFactory)
  Fine level nullspace = Nullspace

  Build (MueLu::CoarseMapFactory)
  Striding info = {}   [default]
  Strided block id = -1   [default]
  Domain GID offsets = {0}   [default]

 [empty list]

 Transpose P (MueLu::TransPFactory)
 [empty list]

 Computing Ac (MueLu::RAPFactory)
 transpose: use implicit = 0   [default]
 Keep AP Pattern = 0   [default]
 Keep RAP Pattern = 0   [default]
 CheckMainDiagonal = 0   [default]
 RepairMainDiagonal = 0

 Setup Smoother (MueLu::IfpackSmoother{type = point relaxation stand-alone})
 relaxation: type = symmetric Gauss-Seidel   [unused]
 relaxation: sweeps = 2   [unused]
 relaxation: damping factor = 1   [unused]

Level 3
 Build (MueLu::TentativePFactory)
  Build (MueLu::UncoupledAggregationFactory)
   Build (MueLu::CoalesceDropFactory)
    Build (MueLu::AmalgamationFactory)
    [empty list]

   aggregation: drop tol = 0   [default]
   aggregation: Dirichlet threshold = 0   [default]
   aggregation: drop scheme = classical   [default]
   lightweight wrap = 0   [default]

  aggregation: mode = old   [default]
  aggregation: max agg size = -1   [default]
  aggregation: min agg size = 1   [unused]
  aggregation: max selected neighbors = 0   [unused]
  aggregation: ordering = natural   [unused]
  aggregation: enable phase 1 = 1   [default]
  aggregation: enable phase 2a = 1   [default]
  aggregation: enable phase 2b = 1   [default]
  aggregation: enable phase 3 = 1   [default]
  aggregation: preserve Dirichlet points = 0   [default]
  UseOnePtAggregationAlgorithm = 0   [default]
  UsePreserveDirichletAggregationAlgorithm = 0   [unused]
  UseUncoupledAggregationAlgorithm = 1   [default]
  UseMaxLinkAggregationAlgorithm = 1   [default]
  UseIsolatedNodeAggregationAlgorithm = 1   [default]
  UseEmergencyAggregationAlgorithm = 1   [default]
  OnePt aggregate map name =    [default]

  Nullspace factory (MueLu::NullspaceFactory)
  Fine level nullspace = Nullspace

  Build (MueLu::CoarseMapFactory)
  Striding info = {}   [default]
  Strided block id = -1   [default]
  Domain GID offsets = {0}   [default]

 [empty list]

 Transpose P (MueLu::TransPFactory)
 [empty list]

 Computing Ac (MueLu::RAPFactory)
 transpose: use implicit = 0   [default]
 Keep AP Pattern = 0   [default]
 Keep RAP Pattern = 0   [default]
 CheckMainDiagonal = 0   [default]
 RepairMainDiagonal = 0

 Setup Smoother (MueLu::IfpackSmoother{type = point relaxation stand-alone})
 relaxation: type = symmetric Gauss-Seidel   [unused]
 relaxation: sweeps = 2   [unused]
 relaxation: damping factor = 1   [unused]

Level 4
 Build (MueLu::TentativePFactory)
  Build (MueLu::UncoupledAggregationFactory)
   Build (MueLu::CoalesceDropFactory)
    Build (MueLu::AmalgamationFactory)
    [empty list]

   aggregation: drop tol = 0   [default]
   aggregation: Dirichlet threshold = 0   [default]
   aggregation: drop scheme = classical   [default]
   lightweight wrap = 0   [default]

  aggregation: mode = old   [default]
  aggregation: max agg size = -1   [default]
  aggregation: min agg size = 1   [unused]
  aggregation: max selected neighbors = 0   [unused]
  aggregation: ordering = natural   [unused]
  aggregation: enable phase 1 = 1   [default]
  aggregation: enable phase 2a = 1   [default]
  aggregation: enable phase 2b = 1   [default]
  aggregation: enable phase 3 = 1   [default]
  aggregation: preserve Dirichlet points = 0   [default]
  UseOnePtAggregationAlgorithm = 0   [default]
  UsePreserveDirichletAggregationAlgorithm = 0   [unused]
  UseUncoupledAggregationAlgorithm = 1   [default]
  UseMaxLinkAggregationAlgorithm = 1   [default]
  UseIsolatedNodeAggregationAlgorithm = 1   [default]
  UseEmergencyAggregationAlgorithm = 1   [default]
  OnePt aggregate map name =    [default]

  Nullspace factory (MueLu::NullspaceFactory)
  Fine level nullspace = Nullspace

  Build (MueLu::CoarseMapFactory)
  Striding info = {}   [default]
  Strided block id = -1   [default]
  Domain GID offsets = {0}   [default]

 [empty list]

 Transpose P (MueLu::TransPFactory)
 [empty list]

 Computing Ac (MueLu::RAPFactory)
 transpose: use implicit = 0   [default]
 Keep AP Pattern = 0   [default]
 Keep RAP Pattern = 0   [default]
 CheckMainDiagonal = 0   [default]
 RepairMainDiagonal = 0

 Setup Smoother (MueLu::AmesosSmoother{type = Klu})
 [empty list]


--------------------------------------------------------------------------------
---                            Multigrid Summary                             ---
--------------------------------------------------------------------------------
Number of levels    = 5
Operator complexity = 1.49

matrix rows    nnz  nnz/row procs
A 0    9999  29995     3.00  1
A 1    3333   9997     3.00  1
A 2    1111   3331     3.00  1
A 3     371   1111     2.99  1
A 4     124    370     2.98  1

Smoother (level 0) both : MueLu::IfpackSmoother{type = point relaxation stand-alone}

Smoother (level 1) both : MueLu::IfpackSmoother{type = point relaxation stand-alone}

Smoother (level 2) both : MueLu::IfpackSmoother{type = point relaxation stand-alone}

Smoother (level 3) both : MueLu::IfpackSmoother{type = point relaxation stand-alone}

Smoother (level 4) pre  : MueLu::AmesosSmoother{type = Klu}
Smoother (level 4) post : no smoother
