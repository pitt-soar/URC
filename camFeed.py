import cv2
while True:
	ret, frame = cap.read()
	cv2.imshow('Live Video', frame)
	if cv2.waitKey(0) & 0xFF == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()