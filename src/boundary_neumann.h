//
//  boundary_neumann.h
//  AdvancedCFD
//
//  Created by Adrien Lücker on 13/01/15.
//  Copyright (c) 2015 Patrick Jenny. All rights reserved.
//

#ifndef AdvancedCFD_boundary_neumann_h
#define AdvancedCFD_boundary_neumann_h

#include "boundary.h"
#include "grid.h"

/**
 * \brief Class for the computation of boundary fluxes for a Neumann
 *        boundary condition.
 */
class Boundary_Neumann : public Boundary {
  void operator () (Grid* g) const {
    for (int j=0; j < g->n(1); j++) {
      for (int k=0; k < g->n(2); k++) {
        for (int iv=0; iv < g->nv(); iv++) {
          g->f(0,       0, j, k)[iv] = 0.0;
          g->f(0, g->n(0), j, k)[iv] = 0.0;
        }
      }
    }
    for (int i=0; i < g->n(0); i++) {
      for (int k=0; k < g->n(2); k++) {
        for (int iv=0; iv < g->nv(); iv++) {
          g->f(1, i,       0, k)[iv] = 0.0;
          g->f(1, i, g->n(1), k)[iv] = 0.0;
        }
      }
    }
    for (int i=0; i < g->n(0); i++) {
      for (int j=0; j < g->n(1); j++) {
        for (int iv=0; iv < g->nv(); iv++) {
          g->f(2, i, j,       0)[iv] = 0.0;
          g->f(2, i, j, g->n(2))[iv] = 0.0;
        }
      }
    }
  }
};

#endif



