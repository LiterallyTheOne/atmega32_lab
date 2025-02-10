from moviepy.editor import VideoFileClip


def main():
    input_path = "/Users/ramin/ramin_programs/projects/atmega32_lab/docs/figures/SimulIDE_LED_ATMega32_blink.webm"

    output_path = "output_video.gif"

    clip = VideoFileClip(input_path)

    clip.write_gif(output_path, fps=15)

    print(f"GIF saved to {output_path}")


if __name__ == "__main__":
    main()
