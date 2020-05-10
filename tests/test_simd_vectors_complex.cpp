#include <Fastor/Fastor.h>
#include <complex>

using namespace Fastor;

#define Tol 1e-12
#define BigTol 1e-5


template<typename T, size_t N>
std::array<std::complex<T>,N>
zadd(const std::array<std::complex<T>,N> &a, const std::array<std::complex<T>,N> &b) {
    std::array<std::complex<T>,N> out;
    for (size_t i=0; i< N; ++i) out[i] = a[i]+b[i];
    return out;
}
template<typename T, size_t N>
std::array<std::complex<T>,N>
zsub(const std::array<std::complex<T>,N> &a, const std::array<std::complex<T>,N> &b) {
    std::array<std::complex<T>,N> out;
    for (size_t i=0; i< N; ++i) out[i] = a[i]-b[i];
    return out;
}
template<typename T, size_t N>
std::array<std::complex<T>,N>
zmul(const std::array<std::complex<T>,N> &a, const std::array<std::complex<T>,N> &b) {
    std::array<std::complex<T>,N> out;
    for (size_t i=0; i< N; ++i) out[i] = a[i]*b[i];
    return out;
}
template<typename T, size_t N>
std::array<std::complex<T>,N>
zdiv(const std::array<std::complex<T>,N> &a, const std::array<std::complex<T>,N> &b) {
    std::array<std::complex<T>,N> out;
    for (size_t i=0; i< N; ++i) out[i] = a[i]/b[i];
    return out;
}
template<typename T, size_t N>
T
zsum(const std::array<T,N> &a) {
    T out(a[0]);
    for (size_t i=1; i< N; ++i) out += a[i];
    return out;
}
template<typename T, size_t N>
T
zproduct(const std::array<T,N> &a) {
    T out(a[0]);
    for (size_t i=1; i< N; ++i) out *= a[i];
    return out;
}
template<typename T, size_t N>
std::array<T,N>
znorm(const std::array<std::complex<T>,N> &a) {
    std::array<T,N> out;
    for (size_t i=0; i< N; ++i) out[i] = std::norm(a[i]);
    return out;
}
template<typename T, size_t N>
std::array<T,N>
zabs(const std::array<std::complex<T>,N> &a) {
    std::array<T,N> out;
    for (size_t i=0; i< N; ++i) out[i] = std::abs(a[i]);
    return out;
}
template<typename T, size_t N>
std::array<std::complex<T>,N>
zconj(const std::array<std::complex<T>,N> &a) {
    std::array<std::complex<T>,N> out;
    for (size_t i=0; i< N; ++i) out[i] = std::conj(a[i]);
    return out;
}
template<typename T, size_t N>
std::array<T,N>
zarg(const std::array<std::complex<T>,N> &a) {
    std::array<T,N> out;
    for (size_t i=0; i< N; ++i) out[i] = std::arg(a[i]);
    return out;
}




template<typename ABI, typename TT, size_t N>
void test_complex_double_impl(std::array<TT,N> & arr1, std::array<TT,N> & arr2, std::array<TT,N> & arr3) {

    TT diff;
    {
        // Size
        {
            using V = SIMDVector<TT,ABI>;
            FASTOR_EXIT_ASSERT( std::abs(int(V::Size)   - (int)N) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(int(V::size()) - (int)N) < Tol, "TEST FAILED");
        }
        // Load/store
        {
            SIMDVector<TT,ABI> a(arr1.data(),false);
            SIMDVector<TT,ABI> b(arr2.data(),false);

            diff = a.sum() - zsum(arr1);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            diff = b.sum() - zsum(arr2);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            a.load(arr1.data(),false);
            diff = a.sum() - zsum(arr1);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            b.load(arr2.data(),false);
            diff = b.sum() - zsum(arr2);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            a.store(arr1.data(),false);
            diff = a.sum() - zsum(arr1);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            b.store(arr2.data(),false);
            diff = b.sum() - zsum(arr2);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            diff = a.product() - zproduct(arr1);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

            diff = b.product() - zproduct(arr2);
            FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
            FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");
        }


        SIMDVector<TT,ABI> a(arr1.data(),false);
        SIMDVector<TT,ABI> b(arr2.data(),false);

        // vector-vector
        // addition
        diff = (a+b).sum() - zsum(zadd(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // subtraction
        diff = (a-b).sum() - zsum(zsub(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // multiplication
        diff = (a*b).sum() - zsum(zmul(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // division
        diff = (a/b).sum() - zsum(zdiv(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // vector-scalar
        // addition
        diff = (a+arr1[0]).sum() - zsum(zadd(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // subtraction
        diff = (a-arr1[0]).sum() - zsum(zsub(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // multiplication
        diff = (a*arr1[0]).sum() - zsum(zmul(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // division
        diff = (a/arr1[0]).sum() - zsum(zdiv(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");


        // scalar-vector
        // addition
        diff = (arr1[0]+a).sum() - zsum(zadd(arr3,arr1));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // subtraction
        diff = (arr1[0]-a).sum() - zsum(zsub(arr3,arr1));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // multiplication
        diff = (arr1[0]*a).sum() - zsum(zmul(arr3,arr1));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // division
        diff = (arr1[0]/a).sum() - zsum(zdiv(arr3,arr1));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");


        // In-place
        // with another vector
        a += b;
        diff = a.sum() - zsum(zadd(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        a.load(arr1.data(),false);
        a -= b;
        diff = a.sum() - zsum(zsub(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        a.load(arr1.data(),false);
        a *= b;
        diff = a.sum() - zsum(zmul(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        a.load(arr1.data(),false);
        a /= b;
        diff = a.sum() - zsum(zdiv(arr1,arr2));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // with scalar
        a.load(arr1.data(),false);
        a += arr1[0];
        diff = a.sum() - zsum(zadd(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        a.load(arr1.data(),false);
        a -= arr1[0];
        diff = a.sum() - zsum(zsub(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        a.load(arr1.data(),false);
        a *= arr1[0];
        diff = a.sum() - zsum(zmul(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        a.load(arr1.data(),false);
        a /= arr1[0];
        diff = a.sum() - zsum(zdiv(arr1,arr3));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");


        // norm
        a.load(arr1.data(),false);
        FASTOR_EXIT_ASSERT( std::abs( a.norm().sum() - zsum(znorm(arr1)) ) < Tol, "TEST FAILED");

        // abs
        a.load(arr1.data(),false);
        FASTOR_EXIT_ASSERT( std::abs( abs(a).real().sum() - zsum(zabs(arr1)) ) < Tol, "TEST FAILED");

        // conj
        a.load(arr1.data(),false);
        diff = conj(a).sum() - zsum(zconj(arr1));
        FASTOR_EXIT_ASSERT( std::abs(diff.real()) < Tol, "TEST FAILED");
        FASTOR_EXIT_ASSERT( std::abs(diff.imag()) < Tol, "TEST FAILED");

        // arg
        a.load(arr1.data(),false);
        FASTOR_EXIT_ASSERT( std::abs( arg(a).real().sum() - zsum(zarg(arr1)) ) < BigTol, "TEST FAILED");

    }

    print(FGRN(BOLD("All tests passed successfully")));
}


template<typename T, typename ABI>
void test_complex_double();
template<>
void test_complex_double<double,simd_abi::sse>() {
    using TT = std::complex<double>;
    // These arrays are used to mimick complex SIMDVector
    std::array<TT,2> arr1 = {TT(3,-4),TT(7,12)};
    std::array<TT,2> arr2 = {TT(6,14),TT(-5,1.2)};
    std::array<TT,2> arr3 = {arr1[0],arr1[0]};
    test_complex_double_impl<simd_abi::sse>(arr1,arr2,arr3);
}
template<>
void test_complex_double<double,simd_abi::avx>() {
    using TT = std::complex<double>;
    // These arrays are used to mimick complex SIMDVector
    std::array<TT,4> arr1 = {TT(3,-4),TT(7,12),TT(5,-2),TT(11,9)};
    std::array<TT,4> arr2 = {TT(6,14),TT(-5,1.2),TT(0,8),TT(1,15)};
    std::array<TT,4> arr3 = {arr1[0],arr1[0],arr1[0],arr1[0]};
    test_complex_double_impl<simd_abi::avx>(arr1,arr2,arr3);
}



int main() {

    print(FBLU(BOLD("Testing SIMDVector of complex double precision")));
    test_complex_double<double,simd_abi::sse>();
    test_complex_double<double,simd_abi::avx>();

    return 0;
}