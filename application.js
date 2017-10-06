var text = new Array(
	"> morsekode",
	"> skriv morskekode ved at trykke på knappen",
	"> "
);

var notTyping = false;
var caret = "<div id='caret'>|</div>"
var delay = 100; // time delay of print out
var scroll = 5; // start scrolling up at this many lines
var linePos = 0; // start printing array at this posision
var textPos = 0; // initialise text position
var textLength = text[0].length; // the length of the text array 
var iRow; // initialise current row
var content = ''; // initialise contents variable


function typewriter() {
	content = ' ';
	iRow = Math.max(0, linePos - scroll);
	var destination = document.getElementById("typedtext");
	while (iRow < linePos) {
		content += text[iRow++] + '<br />';
	}

	destination.innerHTML = content + text[linePos].substring(0, textPos) + caret;

	if (textPos++ == textLength) {
		textPos = 0;
		linePos++;
		if (linePos != text.length) {
			textLength = text[linePos].length;
			setTimeout("typewriter()", 500);
		} else {
			notTyping = true;
		}
	} else {
		setTimeout("typewriter()", delay);
	}
}


typewriter();


function addChar(key) {
	if (notTyping) {
		var destination = document.getElementById("typedtext");
		content = destination.innerHTML;
		text[text.length - 1] += key;
		destination.innerHTML = content.substring(0, content.length - caret.length) + key + caret;
	}
}


function newLine() {
	if (notTyping) {
		notTyping = false;
		text.push("> ");
		typewriter();
	}
}


document.onkeydown = function(event) {
	if (event.keyCode === 13) {
		newLine();
	} else {
		var pressedKey = String.fromCharCode(event.keyCode);
		addChar(pressedKey.toLowerCase());
	}
}