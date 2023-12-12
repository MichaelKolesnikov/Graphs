let isDragging = false;
let startPosition = { x: 0, y: 0 };
let offset = { x: 0, y: 0 };

const movableImage = document.getElementById('movableImage');

movableImage.addEventListener('mousedown', (e) => {
    isDragging = true;
    startPosition.x = e.clientX;
    startPosition.y = e.clientY;
    offset.x = e.clientX - movableImage.offsetLeft;
    offset.y = e.clientY - movableImage.offsetTop;
    movableImage.style.cursor = 'grabbing';
});

document.addEventListener('mousemove', (e) => {
    if (isDragging) {
        const x = e.clientX - offset.x;
        const y = e.clientY - offset.y;

        movableImage.style.left = x + 'px';
        movableImage.style.top = y + 'px';
    }
});

document.addEventListener('mouseup', () => {
    isDragging = false;
    movableImage.style.cursor = 'grab';
});
