//
//  init_nscompressible.h
//  AdvancedCFD
//
//  Created by Patrick Jenny on 05/01/15.
//  Copyright (c) 2015 Patrick Jenny. All rights reserved.
//

#ifndef AdvancedCFD_init_nscompressible_h
#define AdvancedCFD_init_nscompressible_h

#include "init.h"
#include <stdio.h>

class State_Equation;

/**
 * \brief Initial condition for the compressible Navier-Stokes equations
 */
class Init_NSCompressible : public Init {
public:
  Init_NSCompressible    (Control* c, State_Equation* eq)
  : Init(c),
    _eq(eq)
  {}
  ~Init_NSCompressible   ()           {}
  /**
   * Defines the initial condition given an entry in the control file.
   * - 1: 1D Riemann problem
   * - 2: uniform field
   */
  void operator () (Grid* g) const {
    switch (_c->getInt("Case_Init")) {
      case 1:  init_1d_RiemannProblem(g);    break;
      case 2:  init_1d_sin           (g);    break;
      case 3:  init_2d_uniform       (g);    break;
      case 4:  init_2d_sin           (g);    break;
      default: printf("\nInitial condition not defined\n"); break;
    }
  }
private:
  void init_1d_RiemannProblem (Grid* g) const;
  void init_1d_sin            (Grid* g) const;
  void init_2d_uniform        (Grid* g) const;
  void init_2d_sin            (Grid* g) const;
  State_Equation* _eq;
};

#endif
