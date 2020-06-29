<?php
	header("content-type:text/html;charset=utf-8");         //设置编码
	$myfile_read = fopen("data_2.txt", "r") or die("Unable to open file!");
	$myfile_write = fopen("result.txt", "w") or die("Unable to open file!");
	// 输出单行直到 end-of-file
	ob_end_clean();     //在循环输出前，要关闭输出缓冲区   
	while(!feof($myfile_read)) {
	  $line= trim(fgets($myfile_read));
	  $splite_result=explode(",",$line);
	  $OrignX=trim($splite_result[0]);
	  $OrignY=trim($splite_result[1]);
	  $DestX=trim($splite_result[2]);
	  $DestY=trim($splite_result[3]);
	  $url="http://restapi.amap.com/v3/direction/driving?key=065481073b2b058ab2a4f972e4d6e9f4&origin=".$OrignX.",".$OrignY."&destination=".$DestX.",".$DestY."&originid=&destinationid=&extensions=base&strategy=0&waypoints=&avoidpolygons=&avoidroad=";
	  
	  $result= do_get($url);
	  $arr = json_decode($result, true);
	  //$write_result=$line.",".$arr['route']['paths'][0]['distance'].",".$arr['route']['paths'][0]['duration']."\n";
	  $write_result=$arr['route']['paths'][0]['distance'].",".$arr['route']['paths'][0]['duration']."\n";
	  //写入文件
	  fwrite($myfile_write,$write_result);
	  echo $write_result."<br>";
	  flush(); 
	}
	//关闭文件
	fclose($myfile_read);
	fclose($myfile_write);

	function do_get($url) {    
	    $ch = curl_init ();
        curl_setopt ( $ch, CURLOPT_URL, $url );
        curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, 1 );
        curl_setopt ( $ch, CURLOPT_CUSTOMREQUEST, 'GET' );
        curl_setopt ( $ch, CURLOPT_TIMEOUT, 60 );         
        $result = curl_exec ( $ch );
        curl_close ( $ch );        
        return $result;
    }
?>