#pragma once

// Ŭ���� ���漱��
class animation;

class image
{
public:
	typedef struct tagImage
	{
		ID2D1Bitmap*	bitmap;			// ��Ʈ��
		fPOINT			size;			// ũ��
		POINT			maxFrame;		// �ִ� ������ ��
		fPOINT			frameSize;		// ������ ũ��

		tagImage()
		{
			bitmap		= NULL;
			size		= { 0.f, 0.f };
			maxFrame	= { 0, 0 };
			frameSize	= { 0.f, 0.f };
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*		_imageInfo;		//�̹��� ����
	wstring			_fileName;		//�̹��� �̸�

private :
	HRESULT _putImage(void);
	void	_putImageInfo(void);

public:
	// ������ �ʱ�ȭ
	HRESULT init(const wchar_t * fileName);
	HRESULT init(const wchar_t * fileName, int maxFrameX, int maxFrameY);

	//����
	void release(void);

	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(float alpha = 1.0f);

	// �̹��� Ŭ����
	void render(float clipX, float clipY, float clipW, float clipH, float alpha = 1.0f, D2D1_POINT_2F center = { -1.f, -1.f });

	// ������ ����
	void frameRender(int frameX, int frameY, float alpha = 1.0f);
	void frameRender(fPOINT frame, float alpha = 1.0f);

	// �ִ� ����
	void aniRender(animation * ani, float alpha = 1.0f);

	// ���� ���� : ȸ�� ��ȿȭ
	void loopRender(fRECT * range, fPOINT offset = 0.f, int frameX = 0, int frameY = 0, float alpha = 1.f);
	void loopRender(fRECT * range, fPOINT offset = 0.f, float frameSizeX = 0, float frameSizeY = 0, float alpha = 1.f);

public :
	// =========================== inline ============================== //
	// �̹��� ����, ����ũ��
	inline const fPOINT & getSize(void) { return _imageInfo->size; };

	// �̹��� 1������ ����, ���� ũ��
	inline const fPOINT & getFrameSize(void) { return _imageInfo->frameSize; }

	// �̹��� ������ ����
	inline const POINT & getMaxFrame(void) { return _imageInfo->maxFrame; };

	// �߾���ǥ
	inline fPOINT getCenterPos(void) { return _imageInfo->size / 2.0f; }
	inline fPOINT getCenterFramePos(void) { return _imageInfo->frameSize / 2.0f; };

	image();
	~image() {}
};