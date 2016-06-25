//
//  setup_nscompressible.h
//  AdvancedCFD
//
//  Created by Patrick Jenny on 05/01/15.
//  Copyright (c) 2015 Patrick Jenny. All rights reserved.
//

#ifndef AdvancedCFD_setup_nscompressible_h
#define AdvancedCFD_setup_nscompressible_h

#include "setup.h"
#include "init_nscompressible.h"
#include "plot_nscompressible.h"
#include "fluxes_nscompressible.h"
#include "source_nscompressible.h"
#include "boundary_periodic.h"
#include "boundary_neumann.h"
#include "boundary_supersonic_inlet.h"
#include "update_standard.h"
#include "state_equation_polytropic.h"

/**
 * \brief Simulation setup for the compressible Navier-Stokes equations
 */
class Setup_NSCompressible : public Setup {
public:
	/**
	 * Constructor that allocates all member pointers
	 *
	 * The control file "nsCompressible.ctr" is used for the setup.
	 *
	 * The arguments are passed as double pointers (of type Class**)
	 * and the corresponding pointers (of type Class*) are allocated in this constructor.
	 * Therefore, the caller has access to all created objects.
	 */
  Setup_NSCompressible (Control** c, Time** t, Grid** g, Init** i, Boundary** b,
                   Fluxes** f, Source** q, Update** u, Plot** p, Postprocess** pp) {
    _c  = (*c) = new Control("nsCompressible.ctr");
    _c->read();
    _eq        = new State_Equation_Polytropic(_c->getDouble("gamma"));
    _g  = (*g) = new Grid(5, 0, _c->getInt("n",1), _c->getInt("n",2), _c->getInt("n",3),
                          _c->getDouble("lx",1), _c->getDouble("lx",2), _c->getDouble("lx",3));
    _t  = (*t) = new Time(_c->getInt("nt"), _c->getInt("nout"), _c->getDouble("dt"));
    _i  = (*i) = new Init_NSCompressible  (_c, _eq);
    switch (_c->getInt("Case_Boundary")) {
      case 1:   _b = (*b) = new Boundary_Neumann; break;
      case 2:   _b = (*b) = new Boundary_Supersonic_Inlet(_c, _eq); break;
      default:  _b = (*b) = new Boundary_Periodic; break;
    }
    _f  = (*f) = new Fluxes_NSCompressible(_c, _g, _eq);
    _q  = (*q) = new Source_NSCompressible(_c, _g, _t);
    _u  = (*u) = new Update_Standard;
    _p  = (*p) = new Plot_NSCompressible  (_c);
   // _pp = (*pp)= new Postprocess_Empty    (_c);
  }
  /**
   * Destructor that deletes all pointers
   */
  virtual ~Setup_NSCompressible () {
    delete _eq;
  }
private:
  State_Equation* _eq;
};

Bug fixed
#endif
