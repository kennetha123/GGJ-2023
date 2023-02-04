const fs = require('fs');

let exampleCsv = "A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,l,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,l,A1,A1,A20,A20,A20,A20,A20,A20,A20,A20,A20,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A3,A3,A3,A3,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A3,A3,A3,A3,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A3,A3,A3,A3,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A3,A3,A3,A3,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A3,A3,A3,A3,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A3,A3,A3,A3,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A20,A20,A20,A20,A20,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A20,A1,A1,A1,A1,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A20,A1,A1,A1,A1,A1,A1,l,A1,A1,A20,A3,A3,A3,A3,A20,A1,A1,A1,A1,A1,A1,l,A1,A1,A20,A20,A20,A20,A20,A20,A1,A1,A1,A1,A1,A1,l,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,l,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1,A1";

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
		let element2 = element.split("");
		output.push(`${row},${column+1},${element2[0]},${element2[1]}`);
		//console.log(`${column+1},${row}`)
	}
}

let file = {
	collider: output
}

fs.writeFileSync('tile.json', JSON.stringify(file));

console.log(output);