function turnOn(bulbNumber) {
  fetch(`http://localhost:8080/bulb/${bulbNumber}/on`, {
    method: 'POST'
  })
  .then(res => res.text())
  .then(data => console.log(data))
  .catch(err => console.error('Error:', err));
}

function turnOff(bulbNumber) {
  fetch(`http://localhost:8080/bulb/${bulbNumber}/off`, {
    method: 'POST'
  })
  .then(res => res.text())
  .then(data => console.log(data))
  .catch(err => console.error('Error:', err));
}
