const testAddon = require('./build/Release/testaddon.node');
//var PNGImage = require('pngjs-image');

console.log('===================');
 console.log('사용가능함수들:',testAddon);
console.log('===================');

/*
console.log("헬로");
console.log(testAddon.hello());
console.log("헬로");
console.log(testAddon.GetCursor());
console.log(testAddon.SetCursor(0,0));a
*/




//console.log(testAddon.IsterminateCalibration());
console.log("bbbbbbbb");

/*
console.log(testAddon.ClickMouseLeft());


console.log(testAddon.PressKeyboard(65)); //122  
*/

//https://docs.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
	//가상키코드

/*
    var myresults1= testAddon.ConnectCamera();
    console.log("카메라 연결시도"+myresults1);

var count=0;
var imagearray;

setTimeout(function(){
   abcccc
   imagearray = testAddon.CaptureCamera();

   
   for(var i = 0 ; i<10;  i++)
   {
      console.log(imagearray[i]);
   }
   //console.log("총길이:"+imagearray.length);
   

   var buffer1 = new Buffer(imagearray.length);

   buffer1 = imagearray;
   console.log(buffer1);
   //console.log("버퍼길이:"+buffer1.length);





   var myresults3 = testAddon.DisConnectCamera();
   console.log("카메라 연결해제"+myresults3);

},100);

*/



/*
function intervalFunc(){
   count++;
    var myresults2= testAddon.CaptureCamera();
    console.log("카메라 캡쳐시도"+myresults2);

   if(count==10){
	clearInterval(tempinterval);
      console.log("10장찍음 해제");
	  var myresults3 = testAddon.DisConnectCamera();
      console.log("카메라 연결해제"+myresults3);
   }
	
}
var tempinterval=setInterval(intervalFunc, 1000);
*/

//39296 까지 줄여야함..  jpg 포멧인듯



/*
 console.log('hello 함수테스트',testAddon.hello());
console.log('===================');
console.log('add 함수테스트', testAddon.add(5, 10));
console.log('===================');
console.log('=======5초간 안나올걸=========');
 console.log(' 5초 Sleep 함수테스트',testAddon.Sleep(5000));
console.log('===================');
 console.log('myfunction 함수테스트',testAddon.myfunction());
console.log('===================');
*/


module.exports = testAddon;
