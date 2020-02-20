// @HEADER
// ************************************************************************
//
//               Rapid Optimization Library (ROL) Package
//                 Copyright (2014) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact lead developers:
//              Drew Kouri   (dpkouri@sandia.gov) and
//              Denis Ridzal (dridzal@sandia.gov)
//
// ************************************************************************
// @HEADER

#ifndef ROL_NEWTONKRYLOVALGORITHM_B_H
#define ROL_NEWTONKRYLOVALGORITHM_B_H

#include "ROL_Algorithm_B.hpp"
#include "ROL_KrylovFactory.hpp"

/** \class ROL::NewtonKrylovAlgorithm_B
    \brief Provides an interface to run the projected secant algorithm.
*/

namespace ROL {

template<typename Real>
class NewtonKrylovAlgorithm_B : public Algorithm_B<Real> {
private:
  Ptr<Secant<Real>> secant_; ///< Secant object (used for quasi-Newton)
  ESecant esec_;             ///< Secant type
  std::string secantName_;   ///< Secant name

  Ptr<Krylov<Real>> krylov_; ///< Krylov solver object (used for inexact Newton)
  EKrylov ekv_;              ///< Krylov type
  std::string krylovName_;   ///< Krylov name

  int iterKrylov_; ///< Number of Krylov iterations (used for inexact Newton)
  int flagKrylov_; ///< Termination flag for Krylov method (used for inexact Newton)
 
  bool useSecantHessVec_; ///< Whether or not to use to a secant approximation as the Hessian
  bool useSecantPrecond_; ///< Whether or not to use a secant approximation to precondition inexact Newton

  int maxit_;         ///< Maximum number of line search steps (default: 20)
  Real alpha0_;       ///< Initial line search step size (default: 1.0)
  Real rhodec_;       ///< Backtracking rate (default: 0.5)
  Real c1_;           ///< Sufficient Decrease Parameter (default: 1e-4)
  bool useralpha_;    ///< Flag to use user-defined initial step size (default: false)
  bool usePrevAlpha_; ///< Flag to use previous step size as next initial step size (default: false)

  int ls_nfval_;
  int verbosity_;
  bool printHeader_;

  class HessianPNK : public LinearOperator<Real> {
  private:
    const Ptr<Objective<Real>> obj_;
    const Ptr<BoundConstraint<Real>> bnd_;
    const Ptr<const Vector<Real>> x_;
    const Ptr<const Vector<Real>> g_;
    const Real eps_;
    const Ptr<Secant<Real>> secant_;
    const bool useSecant_;
    Ptr<Vector<Real>> v_;
  public:
    HessianPNK(const Ptr<Objective<Real>> &obj,
               const Ptr<BoundConstraint<Real>> &bnd,
               const Ptr<const Vector<Real>> &x,
               const Ptr<const Vector<Real>> &g,
               const Real eps,
               const Ptr<Secant<Real>> &secant,
               const bool useSecant,
               Ptr<Vector<Real>> &pwa)
      : obj_(obj), bnd_(bnd), x_(x), g_(g), eps_(eps), secant_(secant), useSecant_(useSecant), v_(pwa) {}
    void apply(Vector<Real> &Hv, const Vector<Real> &v, Real &tol) const {
      v_->set(v);
      bnd_->pruneActive(*v_,*g_,*x_,eps_);
      if (!useSecant_) obj_->hessVec(Hv,*v_,*x_,tol);
      else             secant_->applyB(Hv,*v_);
      bnd_->pruneActive(Hv,*g_,*x_,eps_);
      v_->set(v);
      bnd_->pruneInactive(*v_,*g_,*x_,eps_);
      Hv.plus(v_->dual());
    }
  };

  class PrecondPNK : public LinearOperator<Real> {
  private:
    const Ptr<Objective<Real>> obj_;
    const Ptr<BoundConstraint<Real>> bnd_;
    const Ptr<const Vector<Real>> x_;
    const Ptr<const Vector<Real>> g_;
    const Real eps_;
    const Ptr<Secant<Real>> secant_;
    const bool useSecant_;
    Ptr<Vector<Real>> v_;
  public:
    PrecondPNK(const Ptr<Objective<Real>> &obj,
               const Ptr<BoundConstraint<Real>> &bnd,
               const Ptr<const Vector<Real>> &x,
               const Ptr<const Vector<Real>> &g,
               Real eps,
               const Ptr<Secant<Real>> &secant,
               const bool useSecant,
               Ptr<Vector<Real>> &dwa)
      : obj_(obj), bnd_(bnd), x_(x), g_(g), eps_(eps), secant_(secant), useSecant_(useSecant), v_(dwa) {}
    void apply(Vector<Real> &Hv, const Vector<Real> &v, Real &tol) const {
      Hv.set(v.dual()); 
    }
    void applyInverse(Vector<Real> &Hv, const Vector<Real> &v, Real &tol) const {
      v_->set(v);
      bnd_->pruneActive(*v_,*g_,*x_,eps_);
      if ( useSecant_ ) secant_->applyH(Hv,*v_);
      else              obj_->precond(Hv,*v_,*x_,tol);
      bnd_->pruneActive(Hv,*g_,*x_,eps_);
      v_->set(v);
      bnd_->pruneInactive(*v_,*g_,*x_,eps_);
      Hv.plus(v_->dual());
    }
  };

  using Algorithm_B<Real>::status_;
  using Algorithm_B<Real>::state_;
  using Algorithm_B<Real>::proj_;

  void initialize(Vector<Real>          &x,
                  const Vector<Real>    &g,
                  Objective<Real>       &obj,
                  BoundConstraint<Real> &bnd,
                  std::ostream &outStream = std::cout); 

  void parseParameterList(ParameterList &list);

public:

  NewtonKrylovAlgorithm_B(ParameterList &list, const Ptr<Secant<Real>> &secant = nullPtr);
  NewtonKrylovAlgorithm_B(ParameterList &list, const Ptr<Krylov<Real>> &krylov,
                          const Ptr<Secant<Real>> &secant = nullPtr);

  using Algorithm_B<Real>::run;
  std::vector<std::string> run( Vector<Real>          &x,
                                const Vector<Real>    &g, 
                                Objective<Real>       &obj,
                                BoundConstraint<Real> &bnd,
                                std::ostream          &outStream = std::cout);

  std::vector<std::string> run( Vector<Real>          &x,
                                const Vector<Real>    &g,
                                Objective<Real>       &obj,
                                BoundConstraint<Real> &bnd,
                                Constraint<Real>      &econ,
                                Vector<Real>          &emul,
                                std::ostream          &outStream = std::cout ) override;

  std::string printHeader( void ) const override;

  std::string printName( void ) const override;

  std::string print( const bool print_header = false ) const override;

}; // class ROL::NewtonKrylovAlgorithm_B

} // namespace ROL

#include "ROL_NewtonKrylovAlgorithm_B_Def.hpp"

#endif
