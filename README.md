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
      ...  
	Output:  
  	  mergedStation-itsLine-Xcoordinate-Ycoordinate  
      182设计园a,高峰专线79路,511841.086319,2505127.930617
      182设计园b,M346路,511855.384055,2505125.553275
      ...

# 2.Get the duration time for every single trip  
  Input:  
      trip records;
      mergedStation records;
  Output:  
      trip records with duration;
      ...


# To be continued...  




