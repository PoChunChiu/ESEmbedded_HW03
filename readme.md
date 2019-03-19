HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [ ] **If you volunteer to give the presentation next week, check this.**

--------------------

#1.實驗目的
	
	了解調用約定與AAPCS

#2.實驗步驟
  #實驗一

1. 本實驗將進行宣告多個函式 _func0~3_ 與宣告單一函式 _func0_ 之差異。

2. 再多個函式宣告後，可於記憶體中看到函式分別的位置，即使不呼叫函式，仍有記憶體存放函式之現象，以及由於引數數目不同而有所差異之函式記憶體。

3. 首先，可由引數差異分辨出宣告之函式，下圖為雙引數之函式 _func1_:

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/dou.JPG)

   下圖為傳遞三引數之函式 _func2_:

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/tri.JPG)



  #實驗二

1. 首先，新增一函式  _int func0()_ ，並呼叫 _func0(1,2) _ 執行 _make qemu_ ， 開始觀察。

2. 可以看到除了r3位置首先出現我們給予的值 "16"，推斷其為 _func0_ 中承接16之位置。

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/r3.JPG)

3. 隨後看到除了r0位置出現我們給予的值 "16"，推斷其為 _func0_ return 16後承接之位置。

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/r0.JPG)
   
且並未觀察將 _r0~r3_ 等以str之指令存入r7之中:

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/nostr.JPG)

4. 另外繼續執行程式多次，可看到程式於 _0xc_ 與 _0x10_ 之間執行，可推斷其為 _while(1)_ 造成之現象。

5. 根據AAPCS， _r0~r3_ 在引數傳遞中會被優先使用，在這邊也可以觀察到。

  #實驗三

1.除實驗一原有 _func0_ 之外，新增一函式  _int func1(int a,int b)_ ，並給予2輸入 _func(1,2) _ 執行 _make qemu_ ， 開始觀察。

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/org_func.JPG)
	
2.可以看到在 _func1_ 的執行過程中，兩個輸入正數 _int a, int b_ 其值分別為1與2被賦予於 _r0,r1_ ，並會將以 _str_ 存入以 _r7_ 後#4與#0之位置。在 _return a+b_ 時再提取至 _r2_ 與 _r3_ 進行 _add_ 。 

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/offset.JPG)

  #實驗四
  
1. 將 *實驗三* 之 _func1_ 移至 _func0_ 中，如:

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/new_func.JPG)

2. 可觀察到函式互相呼叫時，會以 _bl_ 至指定函式，重複前2次實驗之步驟執行程式。

![image](https://github.com/PoChunChiu/ESEmbedded_HW03/blob/master/img/bl.JPG)

#3.結果與結論
	
	
