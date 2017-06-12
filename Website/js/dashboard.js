function floor_3(){
	$("#elevator-picture").animate({marginTop : 0}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 3 });
		//document.getElementById("elevatorPic").src="images/doors_closed.jpg";
	});
}

function floor_2(){
	$("#elevator-picture").animate({marginTop:100}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 2 });
	});
}

function floor_1(){
	$("#elevator-picture").animate({marginTop:200}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 1 });
	});
}

