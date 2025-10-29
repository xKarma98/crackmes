- https://crackmes.one/crackme/68407be02b84be7ea77435d6
- Creator of the challange: OlegBobrov

Disclaimer, I'm not some RE god and also with any paste/post like these you should always try to fact check, I may have inaccuracies here.

# Step 1:
## Getting started with the RE.
I will start by running strings on it to see what is visiable here.
```c
C:\Users\blank\OneDrive\Desktop\mingw64\bin>strings C:\Users\blank\OneDrive\Desktop\crackme.exe
!This program cannot be run in DOS mode.
|$HH
bad allocation
Unknown exception
bad array new length
string too long
bad cast
sCPZSUPgTG@G^C]
Write the secret code:
Your password:
CrackmePassword
Congratulations!!!
Try again
pause
R{@h
R{@h
R{@h
R{@h
RSDS
C:\Projects\Crackme\x64\Release\Crackme.pdb
@08~v-
??1_Lockit@std@@QEAA@XZ
??0_Lockit@std@@QEAA@H@Z
?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A
?_Getgloballocale@locale@std@@CAPEAV_Locimp@12@XZ
?uncaught_exception@std@@YA_NXZ
?cin@std@@3V?$basic_istream@DU?$char_traits@D@std@@@1@A
?_Id_cnt@id@locale@std@@0HA
?id@?$ctype@D@std@@2V0locale@2@A
?_Xlength_error@std@@YAXPEBD@Z
?_Osfx@?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAXXZ
?flush@?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV12@XZ
?_Ipfx@?$basic_istream@DU?$char_traits@D@std@@@std@@QEAA_N_N@Z
?sgetc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZ
?snextc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZ
?sputn@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAA_JPEBD_J@Z
?setstate@?$basic_ios@DU?$char_traits@D@std@@@std@@QEAAXH_N@Z
?sputc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHD@Z
?getloc@ios_base@std@@QEBA?AVlocale@2@XZ
?good@ios_base@std@@QEBA_NXZ
?_Getcat@?$ctype@D@std@@SA_KPEAPEBVfacet@locale@2@PEBV42@@Z
MSVCP140.dll
?_Xbad_alloc@std@@YAXXZ
```

Brief observation we can see ciphertext here and than see some "crackmepassword" Funnily this threw me off.
2, we see the fact this is in c++ and written in visual studio but instead we can use detect it easy to make our point clear.
<img width="913" height="596" alt="adfg" src="https://github.com/user-attachments/assets/e23b852b-a64e-4dc0-9829-ddaa430efa99" />


# Step 2:
Now we want to open our best friend IDA and get some observations done.
Basic observations we will start from sub rsp, 90h we know the windows stack increments downwards so this is the entrypoint from the stack pointer but I will talk relevant to ctf.
We see it prompting for the password with `std::cout` and we see a function call below it.
Write the secret code is also printed by std::cout rax is moved into rcx and sub_1400017D0 is called.
`std::cin` takes the input amd we see another function call.
Juding off the block can assume this may have something to do with the xoring?
A comparison is done with a pointer and 0Fh, when I decompiled it I saw a 0xF. Decompiled line in question involves the key.
`v7 = v5[2] == '\x0F' && memcmp(v6, "CrackmePassword", '\x0F') == 0;`
<img width="645" height="627" alt="p1" src="https://github.com/user-attachments/assets/1ef4e241-4ac5-4e07-80f3-f9bb3ac746e7" />


## Step 2 extended.
rax contains our buffer as it appears to me.
loc_14000150B is our size
rax is added by 0x10 and moved into r8.
jump if zero to loc_14000519 which loads the address of crackmepassword, calls memcompare, tests eax, setz will set bl to 1 if the zero flag was used.

**If not zero.**
zero out bl and jump to loc_14000152A

#### loc_14000152A
Pointer dereference with rbp+57h+block being moved into rdx.
compare 0xF with rdx.
Jump if below or equal to another location, for the sake of time we will go to where this jumps.
<img width="523" height="623" alt="p2" src="https://github.com/user-attachments/assets/f0735415-5c21-437b-a59c-0de059ac245f" />

# location of jump.
As you can see if the condition is met, we will be shown success.
Now jump if not zero to "try again" which if the above failed you will be shown instead.
<img width="655" height="631" alt="p3" src="https://github.com/user-attachments/assets/d2c22b99-f648-44e8-acae-18def845e0e7" />

# Ok, explaination is done we need that secret message.
Refer to solution.py

# Let's see the diassembled code to understand it easier.
```cpp
int __fastcall main(int argc, const char **argv, const char **envp)
{
  __int64 v3; // rax
  __int64 v4; // rax
  __int64 *v5; // rax
  const void *v6; // rcx
  bool v7; // bl
  _BYTE *v8; // rcx
  const char *v9; // rdx
  void *v10; // rcx
  void *v11; // rcx
  void *Block; // [rsp+20h] [rbp-19h] BYREF
  unsigned __int64 v14; // [rsp+38h] [rbp-1h]
  void *v15[2]; // [rsp+40h] [rbp+7h] BYREF
  __int64 v16; // [rsp+50h] [rbp+17h]
  unsigned __int64 v17; // [rsp+58h] [rbp+1Fh]
  void *v18[2]; // [rsp+60h] [rbp+27h] BYREF
  __int64 v19; // [rsp+70h] [rbp+37h]
  unsigned __int64 v20; // [rsp+78h] [rbp+3Fh]

  // 15 bit long key.
  v16 = 15;
  v17 = 15;

  // String copy the ciphertext.
  strcpy((char *)v15, "sCPZSUPgTG@G^C]");
  *(_OWORD *)v18 = 0;
  v19 = 0;
  v20 = 15;
  LOBYTE(v18[0]) = 0;
  // Prompt the user for password, code.
  v3 = sub_1400017D0(std::cout, (__int64)"Your password: ");
  v4 = sub_140001DC0(v3, (__int64)v15, 15u);
  sub_1400017D0(v4, (__int64)"\nWrite the secret code: ");
  sub_1400019B0(std::cin, v18);
  v5 = sub_1400012A0((__int64 *)&Block, (__int64)v15, v18);
  v6 = v5;
  if ( (unsigned __int64)v5[3] > 0xF )
    v6 = (const void *)*v5; // v6 was set to v5 and now is a void ptr.

  // Our key to decrypt is here.
  v7 = v5[2] == '\x0F' && memcmp(v6, "CrackmePassword", '\x0F') == 0;
  if ( v14 > 0xF ) // if v14 is greater than 0xF, we hit congrats.
  {
    v8 = Block; // v8 is set to our block.
    if ( v14 + 1 >= 0x1000 ) // v14 + 1 if this is larger than or equal to we get a invalid parameter.
    {
      v8 = (_BYTE *)*((_QWORD *)Block - 1);
      if ( (unsigned __int64)((_BYTE *)Block - v8 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v8); // And free the memory.
  }
  v9 = "\nCongratulations!!!\n";
  if ( !v7 )
    v9 = "\nTry again\n";
  sub_1400017D0(std::cout, (__int64)v9);
  system("pause");
  if ( v20 > 0xF )
  {
    v10 = v18[0];
    if ( v20 + 1 >= 0x1000 )
    {
      v10 = (void *)*((_QWORD *)v18[0] - 1);
      if ( (unsigned __int64)((char *)v18[0] - (char *)v10 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v10);
  }
  if ( v17 > 0xF )
  {
    v11 = v15[0];
    if ( v17 + 1 >= 0x1000 )
    {
      v11 = (void *)*((_QWORD *)v15[0] - 1);
      if ( (unsigned __int64)((char *)v15[0] - (char *)v11 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v11);
  }
  return 0;
}
```
