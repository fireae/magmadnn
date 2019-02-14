/**
 * @file fill_utilities_host.cpp
 * @author Daniel Nichols
 * @version 0.1
 * @date 2019-02-12
 * 
 * @copyright Copyright (c) 2019
 */

#include "tensor/fill_utilities.h"

namespace skepsi {

template <typename T>
void fill_uniform(memorymanager<T> &m, const std::vector<double>& params) {
    switch (m.get_memory_type()) {
        case HOST:
            // TODO
            break;
            
        #ifdef _HAS_CUDA_
        case DEVICE:
            // TODO
            break;
        case MANAGED:
            // TODO
            break;
        case CUDA_MANAGED:
            // TODO
            break;
        #endif
    }
}
template void fill_uniform(memorymanager<int>&, const std::vector<double>&);
template void fill_uniform(memorymanager<float>&, const std::vector<double>&);
template void fill_uniform(memorymanager<double>&, const std::vector<double>&);


template <typename T>
void fill_glorot(memorymanager<T> &m, const std::vector<double>& params) {
    switch (m.get_memory_type()) {
        case HOST:
            // TODO
            break;
            
        #ifdef _HAS_CUDA_
        case DEVICE:
            // TODO
            break;
        case MANAGED:
            // TODO
            break;
        case CUDA_MANAGED:
            // TODO
            break;
        #endif
    }
}
template void fill_glorot(memorymanager<int>&, const std::vector<double>&);
template void fill_glorot(memorymanager<float>&, const std::vector<double>&);
template void fill_glorot(memorymanager<double>&, const std::vector<double>&);


template <typename T>
void fill_constant(memorymanager<T> &m, const std::vector<double>& params) {
    assert( params.size() >= 1 );

    // assume first param is constant value
    T val = (T) params[0];

    switch (m.get_memory_type()) {
        case HOST:
            for (int i = 0; i < (int) m.get_size(); i++) m.get_host_ptr()[i] = val;
            break;
            
        #ifdef _HAS_CUDA_
        case DEVICE:
            cudaMemset(m.get_device_ptr(), val, m.get_size()*sizeof(T));
            break;
        case MANAGED:
            cudaMemset(m.get_device_ptr(), val, m.get_size()*sizeof(T));
            std::memset(m.get_host_ptr(), val, m.get_size()*sizeof(T));
            break;
        case CUDA_MANAGED:
            std::memset(m.get_cuda_managed_ptr(), val, m.get_size()*sizeof(T));
            m.sync(false);
            break;
        #endif
    }
}
template void fill_constant(memorymanager<int>&, const std::vector<double>&);
template void fill_constant(memorymanager<float>&, const std::vector<double>&);
template void fill_constant(memorymanager<double>&, const std::vector<double>&);


template <typename T>
void fill_zero(memorymanager<T> &m, const std::vector<double>& params) {
    // use fill_constant
    fill_constant(m, {0});
}
template void fill_zero(memorymanager<int>&, const std::vector<double>&);
template void fill_zero(memorymanager<float>&, const std::vector<double>&);
template void fill_zero(memorymanager<double>&, const std::vector<double>&);


template <typename T>
void fill_one(memorymanager<T> &m, const std::vector<double>& params) {
    // use fill_constant
    fill_constant(m, {1});
}
template void fill_one(memorymanager<int>&, const std::vector<double>&);
template void fill_one(memorymanager<float>&, const std::vector<double>&);
template void fill_one(memorymanager<double>&, const std::vector<double>&);

} // namespace skepsi