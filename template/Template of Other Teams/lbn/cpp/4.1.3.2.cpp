for(i=1;i<1<<n;i++){//时间复杂度O(3^n)
	for(j=i;j;j=(j-1)&i)//枚举i的子集，不包括0
		//从f[j]转移到f[i]
}
