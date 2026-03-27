#!/usr/bin/env python3

import argparse
import logging
import re
from pathlib import Path

# -------------------------
# CONFIG
# -------------------------

logging.basicConfig(
    level=logging.INFO,
    format="%(levelname)s: %(message)s"
)

ADDRESS_REGEX = re.compile(
    r'ADDRESS_SHC_[A-Fa-f0-9]{8}_0x[A-Fa-f0-9]{8}'
)
TXT_LINE_REGEX = re.compile(
    r'^\s*(ADDRESS_SHC_[A-Fa-f0-9]{8}_0x[A-Fa-f0-9]{8})\s*\|\s*([\d]*\.?[\d]+)\s*%\s*\|\s*(.*)\s*$'
)

# -------------------------
# FUNCTIONS
# -------------------------

def parse_args():
    parser = argparse.ArgumentParser(description="Process a address header file and generate or update a status file.")
    parser.add_argument("file", help="Header file to process")
    parser.add_argument(
        "folder",
        nargs="?",
        default=None,
        help="Optional folder (defaults to script directory)"
    )
    return parser.parse_args()


def resolve_folder(folder_arg):
    if folder_arg:
        return Path(folder_arg)
    return Path(__file__).parent


def read_header_addresses(file_path):
    if not file_path.exists():
        logging.error(f"Header file not found: {file_path}")
        return []

    content = file_path.read_text()
    matches = ADDRESS_REGEX.findall(content)

    logging.info(f"Found {len(matches)} addresses in header.")
    return matches


def read_existing_txt(txt_path):
    data_map = {}

    if not txt_path.exists():
        logging.info(f"No existing txt file found: {txt_path}")
        return data_map

    logging.info(f"Reading existing txt file: {txt_path}")

    with txt_path.open("r", encoding="utf-8") as f:
        for i, line in enumerate(f, 1):
            line = line.rstrip("\n")

            match = TXT_LINE_REGEX.match(line)
            if not match:
                logging.warning(f"Line {i} malformed: {line}")
                continue

            name, percent, comment = match.groups()

            if name in data_map:
                logging.warning(f"Duplicate entry ignored at line {i}: {name}")
                continue

            data_map[name] = (percent, comment)

    logging.info(f"Loaded {len(data_map)} existing entries.")
    return data_map


def format_line(addr, percent, comment):
    return f"{addr} | {percent}% | {comment}"


def write_output(txt_path, addresses, data_map):
    # Ensure directory exists
    if not txt_path.parent.exists():
        logging.info(f"Creating folder: {txt_path.parent}")
        txt_path.parent.mkdir(parents=True, exist_ok=True)

    logging.info(f"Writing output to: {txt_path}")

    with txt_path.open("w", encoding="utf-8", newline="\n") as f:
        for addr in addresses:
            if addr in data_map:
                percent, comment = data_map.pop(addr)
            else:
                percent = "0.0"
                comment = "Pending"

            # writing
            f.write(format_line(addr, percent, comment) + "\n")

    # logging leftovers
    for leftover, (percent, comment) in data_map.items():
        logging.warning(
            f"Unused entry in previous txt (not in header): {format_line(leftover, percent, comment)}"
        )


# -------------------------
# MAIN
# -------------------------

def main():
    args = parse_args()

    header_path = Path(args.file)
    folder_path = resolve_folder(args.folder)

    logging.info(f"Using folder: {folder_path}")

    addresses = read_header_addresses(header_path)

    if not addresses:
        logging.error("No addresses found in header file. Exiting.")
        raise SystemExit(1)

    txt_filename = header_path.stem + ".txt"
    txt_path = folder_path / txt_filename

    data_map = read_existing_txt(txt_path)

    write_output(txt_path, addresses, data_map)

    logging.info("Done.")


if __name__ == "__main__":
    main()
