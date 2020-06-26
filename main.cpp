#include <cstddef>
#include <cassert>
#include <iostream>
#include "bigint/bigint.hpp"

template <size_t N>
[[nodiscard]] bool miller_rabin(bigint<N> const& n, size_t k) noexcept {
	auto d = n - 1;
	size_t const r = d.trailing_zeros();
	d >>= r;

	while (k--) {
		auto x = pow(bigint<N>::rand(2, n-1), d, n);

		if (x == 1) continue;
		for (size_t i = 0; i < r; i++) {
			if (x == n-1) goto while_label;
			x = mult_ext(x, x) % n;
		}

		return false;

while_label:
		(void)0;
	}

	return true;
}

template <size_t N>
[[nodiscard]] bigint<N> rand_prime() noexcept {
	size_t cnt = 0;
	bigint<N> r;
	do {
		r = bigint<N>::rand();
		r[0] |= 1;
		cnt += 1;
	} while (!miller_rabin(r, 20));

	std::cerr << cnt << '\n';
	return r;
}

int main() {
	auto p = rand_prime<16>();
	std::cerr << p << '\n';

	auto q = rand_prime<16>();
	std::cerr << q << '\n';

	auto n = mult_ext(p, q);
	std::cerr << n << '\n';

	auto phi = mult_ext(p-1, q-1);
	std::cerr << phi << '\n';

	bigint<32> e = 65537;
	std::cerr << e << '\n';

	auto d = e.modinv(phi);
	std::cerr << d << '\n';

	assert(pow(pow(2, e, n), d, n) == 2);
}
