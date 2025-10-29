text = b"sCPZSUPgTG@G^C]"
key = b"CrackmePassword"


decrypt = bytes([text ^ key for text, key in zip(text, key)])
print(decrypt)
