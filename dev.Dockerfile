from skeggib/cpp_dev

run wget https://github.com/bazelbuild/bazelisk/releases/download/v1.8.1/bazelisk-linux-amd64
run chmod +x bazelisk-linux-amd64
run mv bazelisk-linux-amd64 /usr/local/bin/bazel

run apt update
run apt install -y python3
run apt install -y golang
run echo "export PATH=\$PATH:\$HOME/go/bin" >> $HOME/.bashrc

run go install github.com/bazelbuild/buildtools/buildifier@latest

run apt install -y clang-format
