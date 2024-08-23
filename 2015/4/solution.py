import hashlib


def md5_hash(data: str) -> str:
    md5 = hashlib.md5()
    md5.update(data.encode("utf-8"))
    return md5.hexdigest()

key = "bgvyzdsv"
val = 0

# Objective of the code is to find the
# min value that concates with the key
# to produce an md5 hash of 5 leading zeros.

number_of_zeros = 6
leading_zero_str = "0" * number_of_zeros

while True:
    hash_str = key + str(val)
    hash_compute = md5_hash(hash_str)
    if hash_compute[:number_of_zeros] == leading_zero_str:
        break
    else:
        val += 1
print("Minimum Positive Value:", val)
