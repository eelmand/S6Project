function loopDown(){
	$("#elevatorPic").animate({marginTop:100}, 1500, function() {
		$("#example1").sevenSeg({ value: 1 });
		document.getElementById("elevatorPic").src="images/elevator_2.png";
		loopUp();
	});
}

function loopUp(){
	$("#elevatorPic").animate({marginTop : 0}, 1500, function() {
		$("#example1").sevenSeg({ value: 0 });
		document.getElementById("elevatorPic").src="images/doors_closed.jpg";
		loopDown();
	});
}

loopDown();