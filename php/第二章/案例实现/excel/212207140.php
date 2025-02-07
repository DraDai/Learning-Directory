<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>计算机基础题库智能操作版</title>
<style>
html{height:100%;}
body{margin:0;height:100%;color:#333;font-family:Tahoma,simsun;font-size:15px;}
form{margin:0;padding:0;}
.top{position:fixed;background:#369;width:100%;}
.top-title{color:#fff;font-family:'Microsoft YaHei'; font-size:16px; font-weight:bold; text-align:center; line-height:35px;}
.main{min-height:100%;background:#fff;width:100%;margin:0 auto;}
.main-wrap{padding:52px 10px 150px 10px;}
.footer{position:fixed;width:100%;background:#e6e5e5;bottom:0;box-shadow:1px -1px 9px #c2c2c2;font-size:12px;line-height:22px;text-align:center;color:#666;font-family:'Microsoft YaHei';}
.footer ul{list-style:none;}
.footer li{list-style:none;}
.text15 {font-size: 14px;color: #000000;line-height:120%;}
a.y:link {  font-size: 14px; font-family:宋体, 新宋体, Arial; color: #000000; text-decoration: none}
a.y:visited {  font-size: 14px; font-family:宋体, 新宋体, Arial; color: #000000; text-decoration: none}
a.y:hover {  font-size: 14px; font-family:宋体, 新宋体, Arial; color: #FF0000; text-decoration: none}
a.y:active {  font-size: 14px; font-family:宋体, 新宋体, Arial; color: #000000; text-decoration: none}
a.y span{/*color: #000000;*/font-weight:bolder;}
.anchor{position:relative;top:-58px;}
.center{text-align:center;}
.name{margin-top:15px;line-height:25px;}
label{margin-left:10px;padding:5px 0;display:block;cursor:pointer;}
label:hover{background-color:#e5f2ff;}
.result{color:#f00; margin-left:5px;display: inline-block;}
.btn{
    -moz-border-bottom-colors: none;
    -moz-border-left-colors: none;
    -moz-border-right-colors: none;
    -moz-border-top-colors: none;
    background-color: #F5F5F5;
    background-image: linear-gradient(to bottom, #FFFFFF, #E6E6E6);
    background-repeat: repeat-x;
    border-color: rgba(0, 0, 0, 0.1) rgba(0, 0, 0, 0.1) #B3B3B3;
    border-image: none;
    border-radius: 4px;
    border-style: solid;
    border-width: 1px;
    box-shadow: 0 1px 0 rgba(255, 255, 255, 0.2) inset, 0 1px 2px rgba(0, 0, 0, 0.05);
    color: #333333;
    cursor: pointer;
    display: inline-block;
    font-size: 14px;
    line-height: 20px;
    margin-bottom: 0;
    padding: 4px 5px;
    text-align: center;
    text-shadow: 0 1px 1px rgba(255, 255, 255, 0.75);
    vertical-align: middle;
}
</style>
<script>
function getByName(Name){ 
    var i=document.getElementsByName(Name)
       if(i>0){
        return i;
    }else{
        var aEle=document.getElementsByTagName('*'); 
        var arr=[];  
         for(var i=0;i<aEle.length;i++){
         if(aEle[i].getAttribute("name")==Name){
            arr.push(aEle[i])
                }
            }
         return arr; 
        }
    }
function oc(the,b,c,d){
	if(c==1){
		obj = getByName(d);
		check_val=[];
		for(k in obj){
			if(obj[k].checked)
				check_val.push(obj[k].value);
		}
		if(check_val.join('')=='')
		  {
		  alert('没有选中任何选项，请先选择！');
		  return false;
		  }
		if(check_val.join('')==b)
		  document.getElementById(the).innerHTML='回答正确！';
		else
		  document.getElementById(the).innerHTML='回答错误！正确答案是：'+b;
		}
	else
		{
		obj = getByName(d);
		check_val='';
		for(k in obj){
			if(obj[k].checked)
				check_val=obj[k].value;
		}
		if(check_val=='')
		  {
		  alert('没有选中任何选项，请先选择！');
		  return false;
		  }
		if(check_val==b)
		  document.getElementById(the).innerHTML='回答正确！';
		else
		  document.getElementById(the).innerHTML='回答错误！正确答案是：'+b;
		}
}
</script>
</head>
<body>
<div class="top"><div class="top-title">计算机基础题库智能操作版</div></div>
<div class="main">
<div class="main-wrap">
<form>
    <?php
        //导入excel表
        require_once 'Excel/reader.php';
        $data = new Spreadsheet_Excel_Reader();
        $data->setOutputEncoding('UTF-8');
        $data->read('data.xls');
        error_reporting(E_ALL ^ E_NOTICE);

        //提取每行数据
        for ($i = 2; $i <= $data->sheets[0]['numRows']; $i++) {
            //抽取每题的题干和选项类型
            $que_stem = $data->sheets[0]['cells'][$i][1];
            $que_type = $data->sheets[0]['cells'][$i][2];

            //输出题干
            echo "<div class=\"name\">".($i-1)."、$que_stem</div>";

            //判断选项类型
            if($que_type == "多选"){
                //设定选项属性
                $type = "checkbox";
            }else{
                $type = "radio";
            }

            //输出所有选项
            $A = $data->sheets[0]['cells'][$i][3];
            $B = $data->sheets[0]['cells'][$i][4]; 
            $C = null;
            $D = null;
            $C = isset($data->sheets[0]['cells'][$i][5]) ? $data->sheets[0]['cells'][$i][5] : null; 
            $D = isset($data->sheets[0]['cells'][$i][6]) ? $data->sheets[0]['cells'][$i][6] : null;
            $answer = $data->sheets[0]['cells'][$i][7];
            
            echo "<div><label><input type=\"$type\" value=\"A\" name=\"s[$i]\">A、$A</label>";
            echo "<label><input type=\"$type\" value=\"B\" name=\"s[$i]\">B、$B</label>";
            if($C != null){
                echo "<label><input type=\"$type\" value=\"C\" name=\"s[$i]\">C、$C</label>";
            }
            if($D != null){
                echo "<label><input type=\"$type\" value=\"D\" name=\"s[$i]\">D、$D</label>";
            }
            echo "</div>";

            echo "<input type=\"button\" onClick=\"oc('a$i','$answer','$que_type','s[$i]')\" value=\"确定选择并看答案\" class=\"btn\" />";
            echo "<div id=\"a$i\" class=\"result\"></div>";
        }
    ?>
<!-- <div class="name">1、关于Word 2010中的文字上标与下标设置，以下说法正确的是：</div>
<div><label><input type="radio" value="A" name="s[1]">A、只能对阿拉伯数字设置上标或下标</label>
<label><input type="radio" value="B" name="s[1]">B、只能对数字和英文字符设置上标与下标</label>
<label><input type="radio" value="C" name="s[1]">C、上标与下标，针对汉字、英文字符和阿拉伯数字均可设置</label>
<label><input type="radio" value="D" name="s[1]">D、以上说法均不正确</label>
</div>
<input type="button" onClick="oc('a2','C','0','s[1]')" value="确定选择并看答案" class="btn" />
<div id="a2" class="result"></div>
<div class="name">2、Word 2010中使用Alt+Shift+D键，可以：</div>
<div><label><input type="radio" value="A" name="s[2]">A、插入当前日期</label>
<label><input type="radio" value="B" name="s[2]">B、插入当前时间</label>
<label><input type="radio" value="C" name="s[2]">C、插入当前文档的用户名属性</label>
<label><input type="radio" value="D" name="s[2]">D、插入上一次复制的文本内容</label>
</div>
<input type="button" onClick="oc('a3','A','0','s[2]')" value="确定选择并看答案" class="btn" />
<div id="a3" class="result"></div>-->
</form>
<p>有效题库统计： 2</p>
</div>
</div>
<!-- datatime -->
</body>
</html>