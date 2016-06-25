//
//  init_nscompressible.cpp
//  AdvancedCFD
//
//  Created by Patrick Jenny on 05/01/15.
//  Copyright (c) 2015 Patrick Jenny. All rights reserved.
//

#include "init_nscompressible.h"
#include "grid.h"
#include "state_equation.h"
#include <math.h>

void Init_NSCompressible::init_1d_RiemannProblem (Grid* g) const {
  for (int i=0; i < g->n(0); i++) {
    for (int j=0; j < g->n(1); j++) {
      for (int k=0; k < g->n(2); k++) {
        if (g->x(0,i,j,k) >= 0.25 && g->x(0,i,j,k) <= 0.75) {
          g->u(i,j,k)[0] =      2.0;
          g->u(i,j,k)[1] =      0.0;
          g->u(i,j,k)[2] =      0.0;
          g->u(i,j,k)[3] =      0.0;
          g->u(i,j,k)[4] = _eq->energy(2.0, 0.0, 0.0, 0.0, 2e5);
        }
        else {
          g->u(i,j,k)[0] =      1.0;
          g->u(i,j,k)[1] =      0.0;
          g->u(i,j,k)[2] =      0.0;
          g->u(i,j,k)[3] =      0.0;
          g->u(i,j,k)[4] = _eq->energy(1.0, 0.0, 0.0, 0.0, 1e5);
        }
      }
    }
  }
}

void Init_NSCompressible::init_1d_sin (Grid* g) const {
  for (int i=0; i < g->n(0); i++) {
    for (int j=0; j < g->n(1); j++) {
      for (int k=0; k < g->n(2); k++) {
        double u = 100*cos(g->x(0,i,j,k)*2.*M_PI);
        g->u(i,j,k)[0] = 1.0;
        g->u(i,j,k)[1] =   u;
        g->u(i,j,k)[2] = 0.0;
        g->u(i,j,k)[3] = 0.0;
        g->u(i,j,k)[4] = _eq->energy(1.0, u, 0.0, 0.0, 1e5);
      }
    }
  }
}

void Init_NSCompressible::init_2d_uniform (Grid* g) const {
  double r, u, v, w, p, E;
  double _init_values[5];
  for (int i=0; i < 5; i++) {
    _init_values[i] = _c->getDouble("Init_Values",i+1);
  }
  r = _init_values[0];
  u = _init_values[1];
  v = _init_values[2];
  w = _init_values[3];
  p = _init_values[4];
  E = _eq->energy(r, u, v, w, p);
  for (int i=0; i < g->n(0); i++) {
    for (int j=0; j < g->n(1); j++) {
      for (int k=0; k < g->n(2); k++) {
        g->u(i,j,k)[0] = r;
        g->u(i,j,k)[1] = u;
        g->u(i,j,k)[2] = v;
        g->u(i,j,k)[3] = w;
        g->u(i,j,k)[4] = E;
      }
    }
  }
}

void Init_NSCompressible::init_2d_sin (Grid* g) const {
  for (int i=0; i < g->n(0); i++) {
    for (int j=0; j < g->n(1); j++) {
      for (int k=0; k < g->n(2); k++) {
        double u = -100*cos(g->x(0,i,j,k)*2.*M_PI)*sin(g->x(1,i,j,k)*2.*M_PI);
        double v =  100*sin(g->x(0,i,j,k)*2.*M_PI)*cos(g->x(1,i,j,k)*2.*M_PI);
        g->u(i,j,k)[0] = 1.0;
        g->u(i,j,k)[1] = 0.0;
        g->u(i,j,k)[2] = 0.0;
        g->u(i,j,k)[3] = 0.0;
        g->u(i,j,k)[4] = _eq->energy(1.0, u, v, 0.0, 1e5);
      }
    }
  }
}
