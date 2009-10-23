# rippad fran forumet, oversatt till python
# vet inte hur det funkar...

#number = 317584931803
number = 600851475143
divisor=2

while number > 1:
	if number%divisor is 0:
		number /= divisor;
		divisor-=1
	
	divisor+=1

print divisor 
