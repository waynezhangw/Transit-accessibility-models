# Transit-accessibility-models
Modeling transit accessibility and its calculation in C++ based on real big transit data

# 1.Merge chaos bus stations using k-means algorithm
	Input:  
  	  id-station-line-Xcoordinate-Ycoordinate  
  	  28381,182设计园,高峰专线79路,511842.799269000010000,2505130.479450000000000
      25089,182设计园,M346路,511851.960881999980000,2505127.288970000100000  
      25405,182设计园,M324路,511844.956085000010000,2505135.353399999900000
      21393,182设计园,980路,511853.813984000010000,2505126.407550000100000
      24107,182设计园,M273路,511854.638592000000000,2505124.859910000100000
      28432,182设计园,高峰专线79路,511835.503604000030000,2505117.958999999800000
      23479,182设计园,M224路,511861.122760000000000,2505123.656669999900000
      27065,189工业区,M394路,520918.558754000000000,2505945.615230000100000
      27009,189工业区,M394路,520920.130909000000000,2505933.195700000000000
      29319,189工业区,M309路,520908.951590000010000,2505944.554360000000000
      19069,189工业区,907路,520909.880930999990000,2505944.871220000100000
      29507,189工业区,M309路,520921.457262000010000,2505942.580209999800000
      30378,189工业区(临时),M357路,520833.982852999990000,2506034.188159999900000
  	  ...  
	Output:  
  	  mergedStation-itsLine-Xcoordinate-Ycoordinate  
      182设计园a,高峰专线79路,511841.086319,2505127.930617
      182设计园b,M346路,511855.384055,2505125.553275
      189工业区a,M394路,520920.130909,2505933.195700
      189工业区b,M394路,520914.712134,2505944.405255
      189工业区(临时),M357路,520833.982853,2506034.188160
      189工业区(临时站),M357路,520857.677563,2506015.766870
      189工业区后门a,930路,521001.635969,2506111.022690
      189工业区后门b,930路,520894.162367,2505952.319810
      ...



# To be continued...  



