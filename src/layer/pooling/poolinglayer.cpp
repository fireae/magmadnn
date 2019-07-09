/**
 * @file poolinglayer.cpp
 * @author Sedrick Keh
 * @version 0.1.0
 * @date 2019-07-08
 * 
 * @copyright Copyright (c) 2019
 */
#include "layer/pooling/poolinglayer.h"

namespace magmadnn {
namespace layer {

template <typename T>
PoolingLayer<T>::PoolingLayer(op::Operation<T> *input, const std::vector<unsigned int>& filter_shape, const std::vector<unsigned int>& padding,
        const std::vector<unsigned int>& strides, pooling_mode mode, bool propagate_nan)
    : Layer<T>::Layer(input->get_output_shape(), input), mode(mode), propagate_nan(propagate_nan) {

    if (filter_shape.size() == 2) {
        filter_h = filter_shape[0];
        filter_w = filter_shape[1];
    } else {
        fprintf(stderr, "Error: Expected filter_shape to have 2 elements\n");
    }

    if (padding.size() == 2) {
        pad_h = padding[0];
        pad_w = padding[1];
    } else {
        fprintf(stderr, "Error: Expected padding to have 2 elements\n");
    }

    if (strides.size() == 2) {
        stride_h = strides[0];
        stride_w = strides[1];
    } else {
        fprintf(stderr, "Error: Expected strides to have 2 elements\n");
    }

    init();
}

template <typename T>
PoolingLayer<T>::~PoolingLayer() {

}

template <typename T>
std::vector<op::Operation<T> *> PoolingLayer<T>::get_weights() {
    return {};
}

template <typename T>
void PoolingLayer<T>::init() {
    assert( this->input_shape.size() == 4 );

    this->output = op::pooling(this->input, filter_h, filter_w, pad_h, pad_w, stride_h, stride_w, propagate_nan);

    this->name = "Pooling";
}
template class PoolingLayer <int>;
template class PoolingLayer <float>;
template class PoolingLayer <double>;

template <typename T>
PoolingLayer<T>* pooling(op::Operation<T> *input, const std::vector<unsigned int>& filter_shape, const std::vector<unsigned int>& padding,
        const std::vector<unsigned int>& strides, pooling_mode mode, bool propagate_nan) {
    return new PoolingLayer<T>(input, filter_shape, padding, strides, mode, propagate_nan);
}
template PoolingLayer<int>* pooling(op::Operation<int>*, const std::vector<unsigned int>&, const std::vector<unsigned int>&,
        const std::vector<unsigned int>&, pooling_mode, bool);
template PoolingLayer<float>* pooling(op::Operation<float>*, const std::vector<unsigned int>&, const std::vector<unsigned int>&,
        const std::vector<unsigned int>&, pooling_mode, bool);
template PoolingLayer<double>* pooling(op::Operation<double>*, const std::vector<unsigned int>&, const std::vector<unsigned int>&,
        const std::vector<unsigned int>&, pooling_mode, bool);

}   // layer
}   // magmadnn