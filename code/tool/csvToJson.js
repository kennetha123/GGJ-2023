const fs = require('fs');

let exampleCsv = "E,E,E,E,E,E,E,E,E,E,E,E,E,E,l,E,E,E,E,E,E,E,E,E,E,E,E,E,E,l,E,E,X,X,X,X,X,X,X,X,X,X,E,E,l,E,E,X,E,E,E,E,E,E,E,E,X,E,E,l,E,E,X,E,E,E,E,E,E,E,E,X,E,E,l,E,E,X,E,E,E,E,E,E,E,E,X,E,E,l,E,E,X,E,E,E,E,E,E,E,E,X,E,E,l,E,E,X,E,E,E,E,E,E,E,E,X,E,E,l,E,E,X,E,E,E,E,E,E,E,E,X,E,E,l,E,E,X,E,E,E,E,X,X,X,X,X,E,E,l,E,E,X,E,E,E,E,X,E,E,E,E,E,E,l,E,E,X,E,E,E,E,X,E,E,E,E,E,E,l,E,E,X,E,E,E,E,X,E,E,E,E,E,E,l,E,E,X,X,X,X,X,X,E,E,E,E,E,E,l,E,E,E,E,E,E,E,E,E,E,E,E,E,E,l,E,E,E,E,E,E,E,E,E,E,E,E,E,E";

//console.log(exampleCsv);

let array = exampleCsv.split(",");

//console.log(array);

let output = [];
let row = 1;
let column = 1;
for (let index = 0; index < array.length; index++) {
	const element = array[index];
	if (element == "l") {
		row = row + 1;
		column = -1;
	} else {
		column = column + 1;
		//output.push(`${row}`)
		//console.log(column + 1, row, "--- ", element);

		if (element == "X") {
			output.push(`${row},${column+1}`);
		}
		//console.log(`${column+1},${row}`)
	}
}

let file = {
	collider: output
}

fs.writeFileSync('output.json', JSON.stringify(file));

console.log(output);