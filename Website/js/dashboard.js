function floor_3(){
	$("#elevatorPic").animate({marginTop : 0}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 3 });
		//document.getElementById("elevatorPic").src="images/doors_closed.jpg";
	});
}

function floor_2(){
	$("#elevatorPic").animate({marginTop:100}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 2 });
	});
}

function floor_1(){
	$("#elevatorPic").animate({marginTop:200}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 1 });
	});
}

function open_doors(){
	document.getElementById("elevatorPic").src="images/elevator_2.png";
}

function close_doors(){
	document.getElementById("elevatorPic").src="images/doors_closed.jpg";
}