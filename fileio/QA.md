Q1[P63-S78]:
pread不更新当前文件偏移量,可以理解.
pwrite有类似的区别,意思是说也不改变吗?

Q2[P59-S73]:
改善性能都采用某种预读(read ahead)技术,还有延迟写(delayed write)
书中提到Linux上O_SYNC不起效果,看来是不能在程序里面禁用这2个魔法了?
