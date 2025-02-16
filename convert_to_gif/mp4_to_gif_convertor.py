"""Convert mp4 video to a GIF file."""

from moviepy.editor import VideoFileClip


def convert_to_gif(input_path, output_path):
    """Convert mp4 video to a GIF file."""
    clip = VideoFileClip(input_path)
    clip.write_gif(output_path)


def main():
    """main function"""
    input_path = "mp_file.mp4"
    output_path = "output_video.gif"
    convert_to_gif(input_path, output_path)


if __name__ == "__main__":
    main()
