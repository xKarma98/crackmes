This is going to be a very short writeup since this challenge I'd say is great for somebody new to this like I am.

We want to head here and download this challenge:
Author: Eilay_Yosfan
- https://crackmes.one/crackme/690210a42d267f28f69b7980

# How do we start here? I will skip using strings to just flat out use IDA.
1. We figure this code is made in c.
2. We figure out the key.
3. We patch out the jnz to jne. **jnz -> Jump if not zero** **JNE jump if not equal**
<img width="582" height="658" alt="361" src="https://github.com/user-attachments/assets/47bb03e6-8413-410e-bf3e-d3bd447a78bc" />


# Let's go now.
I want to know what's going on in the main function here, I instantly noticed something of interest.
`mov     [rbp+theKey], 44h` With ida I clicked on the 44h the `h` is here because this is 0x44 in hexidecimal

# To figure out the true value being added to rbp we head here.
RBP is our base pointer, in which is of interest if we see this moving here and again being compared before our if statement at the bottom of the code.
https://www.rapidtables.com/convert/number/hex-to-decimal.html?x=44 We can see a conversion to `68`

# Ok results??
Upon entering 68 we successfully pass and beat this challange.


# Recreation of the code will be applied in sample.c
