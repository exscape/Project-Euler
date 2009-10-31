def factorize(orig_n):
	factors = []
	n = orig_n
	i = 2
	sq_i = i*i
	while sq_i <= n:
		while n % i == 0:
			n /= i
			factors.append(i)
		sq_i += 2 * i + 1
		i += 1
	if (n != 1) and (n != orig_n):
		factors.append(n)
	
	return factors

def product(l):
	return reduce(lambda x,y: x*y, l)

for i in range(1,1001):
	factors = factorize(i)
	if len(factors) != 0: # not prime
		print "{0}: {1} == {2}".format(i, factorize(i), product(factorize(i)))
		if product(factors) != i:
			print "ERROR at {0}: product(factorize{1}) returned {2}".format(i, i, product(factors))
	else:
		print "{0}: prime".format(i)
