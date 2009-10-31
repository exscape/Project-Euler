def factorize(x):
	factors = {}
	n = x
	i = 2
	sq_i = i*i
	while sq_i <= n:
		while n % i == 0:
			n /= i
			if (i not in factors.keys()):
				factors[i] = 1
			else:
				factors[i] += 1
		sq_i += 2 * i + 1
		i += 1
	if (n != 1) and (n != x):
		if (n not in factors.keys()):
			factors[n] = 1
		else:
			factors[n] += 1
	return factors

for i in range(1,102):
	print "{0}: {1}".format(i, factorize(i))
