/*
//@HEADER
// ************************************************************************
//
//               KokkosKernels: Linear Algebra and Graph Kernels
//                 Copyright 2016 Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
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
// Questions? Contact Siva Rajamanickam (srajama@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef _KOKKOSSPGEMMVIENNACL_HPP
#define _KOKKOSSPGEMMVIENNACL_HPP

//#define KERNELS_HAVE_VIENNACL


#ifdef KERNELS_HAVE_VIENNACL
#define VIENNACL_WITH_CUDA
#include "viennacl/compressed_matrix.hpp"
#include "viennacl/linalg/prod.hpp"
#include "viennacl/linalg/host_based/common.hpp"

#endif

#include "KokkosKernels_Utils.hpp"
namespace KokkosKernels{

namespace Experimental{

namespace Graph{
namespace Impl{




  template <typename KernelHandle,
  typename in_row_index_view_type,
  typename in_nonzero_index_view_type,
  typename in_nonzero_value_view_type,
  typename bin_row_index_view_type,
  typename bin_nonzero_index_view_type,
  typename bin_nonzero_value_view_type,
  typename cin_row_index_view_type,
  typename cin_nonzero_index_view_type,
  typename cin_nonzero_value_view_type>
  void viennaCL_apply(
      KernelHandle *handle,
      typename KernelHandle::nnz_lno_t m,
      typename KernelHandle::nnz_lno_t n,
      typename KernelHandle::nnz_lno_t k,
      in_row_index_view_type row_mapA,
      in_nonzero_index_view_type entriesA,
      in_nonzero_value_view_type valuesA,

      bool transposeA,
      bin_row_index_view_type row_mapB,
      bin_nonzero_index_view_type entriesB,
      bin_nonzero_value_view_type valuesB,
      bool transposeB,
      cin_row_index_view_type row_mapC,
      cin_nonzero_index_view_type &entriesC,
      cin_nonzero_value_view_type &valuesC,
      bool verbose = false){

#ifdef KERNELS_HAVE_VIENNACL

    typedef typename KernelHandle::nnz_lno_t idx;
    typedef in_row_index_view_type idx_array_type;

    typedef typename KernelHandle::nnz_scalar_t value_type;


    typedef typename in_row_index_view_type::device_type device1;
    typedef typename in_nonzero_index_view_type::device_type device2;
    typedef typename in_nonzero_value_view_type::device_type device3;

    typedef typename KernelHandle::HandleExecSpace MyExecSpace;

    typedef typename viennacl::compressed_matrix<value_type>::handle_type it;
    typedef typename viennacl::compressed_matrix<value_type>::value_type vt;

    if ((Kokkos::Impl::is_same<idx, int>::value && Kokkos::Impl::is_same<typename KernelHandle::size_type, int>::value )||
        (Kokkos::Impl::is_same<idx, unsigned int>::value && Kokkos::Impl::is_same<typename KernelHandle::size_type, unsigned int>::value ) ||
        (Kokkos::Impl::is_same<idx, it>::value && Kokkos::Impl::is_same<typename KernelHandle::size_type, it>::value )
        ){

      unsigned int * a_xadj = (unsigned int *)row_mapA.ptr_on_device();
      unsigned int * b_xadj = (unsigned int * )row_mapB.ptr_on_device();
      unsigned int * c_xadj = (unsigned int * )row_mapC.ptr_on_device();

      unsigned int * a_adj = (unsigned int * )entriesA.ptr_on_device();
      unsigned int * b_adj = (unsigned int * )entriesB.ptr_on_device();
      unsigned int * c_adj = (unsigned int * )entriesC.ptr_on_device();

      int nnzA = entriesA.dimension_0();
      int nnzB = entriesB.dimension_0();

      value_type *a_ew = valuesA.ptr_on_device();
      value_type *b_ew = valuesB.ptr_on_device();
      value_type *c_ew = valuesC.ptr_on_device();



      /*
        std::cout << "create a" << std::endl;
        std::cout << "m:" << m << " n:" << n << std::endl;
        std::cout << "a_xadj[0]:" << a_xadj[0] << " a_xadj[m]:" << a_xadj[m] << std::endl;
        std::cout << "a_adj[a_xadj[m] - 1]:" << a_adj[a_xadj[m] - 1] << " a_ew[a_xadj[m] - 1]:" << a_ew[a_xadj[m] - 1] << std::endl;
       */


      Kokkos::Impl::Timer timerset;
      if (verbose)
	std::cout << "viennacl matrix create begins here" << std::endl;
#ifdef VIENNACL_WITH_CUDA
      viennacl::compressed_matrix<value_type> A(a_xadj, a_adj, a_ew, viennacl::CUDA_MEMORY , m, n, nnzA);
      viennacl::compressed_matrix<value_type> B(b_xadj, b_adj, b_ew, viennacl::CUDA_MEMORY, n, k, nnzB);
#else 
      viennacl::compressed_matrix<value_type> A(a_xadj, a_adj, a_ew, viennacl::MAIN_MEMORY, m, n, nnzA);
      viennacl::compressed_matrix<value_type> B(b_xadj, b_adj, b_ew, viennacl::MAIN_MEMORY, n, k, nnzB);

#endif
      //viennacl::compressed_matrix<value_type> A;
      //viennacl::compressed_matrix<value_type> B;
      //A.set(a_xadj, a_adj, a_ew, m, n, nnzA);
      //B.set(b_xadj, b_adj, b_ew, n, k, nnzB);
      if (verbose)
      std::cout << "VIENNACL compress matrix create:" << timerset.seconds() << std::endl;


      Kokkos::Impl::Timer timer1;
      viennacl::compressed_matrix<value_type> C = viennacl::linalg::prod(A, B);
      MyExecSpace::fence();

      if (verbose)
      std::cout << "Actual VIENNACL SPMM Time:" << timer1.seconds() << std::endl;

      {



        unsigned int c_rows = m, c_cols = k, cnnz = C.nnz();

#ifdef VIENNACL_WITH_CUDA
        value_type   const * values   = viennacl::cuda_arg<value_type>(C.handle());
        unsigned int const * rows_start = viennacl::cuda_arg<unsigned int>(C.handle1());
        unsigned int const * columns = viennacl::cuda_arg<unsigned int>(C.handle2());
#else 
        value_type   const * values   = viennacl::linalg::host_based::detail::extract_raw_pointer<value_type>(C.handle());
        unsigned int const * rows_start = viennacl::linalg::host_based::detail::extract_raw_pointer<unsigned int>(C.handle1());
        unsigned int const * columns = viennacl::linalg::host_based::detail::extract_raw_pointer<unsigned int>(C.handle2());

#endif

        {
          Kokkos::Impl::Timer copy_time;
          //row_mapC = typename cin_row_index_view_type::non_const_type(Kokkos::ViewAllocateWithoutInitializing("rowmapC"), c_rows + 1);
          entriesC = typename cin_nonzero_index_view_type::non_const_type (Kokkos::ViewAllocateWithoutInitializing("EntriesC") , cnnz);
          valuesC = typename cin_nonzero_value_view_type::non_const_type (Kokkos::ViewAllocateWithoutInitializing("valuesC") ,  cnnz);
	  MyExecSpace::fence();
          KokkosKernels::Experimental::Util::copy_vector<unsigned int const *, typename cin_row_index_view_type::non_const_type, MyExecSpace> (m, rows_start, row_mapC);
          KokkosKernels::Experimental::Util::copy_vector<unsigned int const *, typename cin_nonzero_index_view_type::non_const_type, MyExecSpace> (cnnz, columns, entriesC);
          KokkosKernels::Experimental::Util::copy_vector<value_type   const *, typename cin_nonzero_value_view_type::non_const_type, MyExecSpace> (cnnz, values, valuesC);
          MyExecSpace::fence();


          double copy_time_d = copy_time.seconds();
          if (verbose)
          std::cout << "VIENNACL COPYTIME:" << copy_time_d << std::endl;
        }

      }
    }
    else {
      throw std::runtime_error ("VIENNACL requires local ordinals to be integer.\n");
    }
#else
    throw std::runtime_error ("VIENNACL IS NOT DEFINED\n");
    return;
#endif
  }
}
}
}
}

#endif
