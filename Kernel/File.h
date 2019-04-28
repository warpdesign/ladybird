#include <AK/Retainable.h>
#include <AK/Types.h>
#include <Kernel/FileSystem/FileDescriptor.h>

class Process;

class File : public Retainable<File> {
public:
    virtual ~File();

    virtual KResultOr<Retained<FileDescriptor>> open(int options);
    virtual void close();

    virtual bool can_read(Process&) const = 0;
    virtual bool can_write(Process&) const = 0;

    virtual ssize_t read(Process&, byte*, ssize_t) = 0;
    virtual ssize_t write(Process&, const byte*, ssize_t) = 0;
    virtual int ioctl(Process&, unsigned request, unsigned arg);
    virtual KResultOr<Region*> mmap(Process&, LinearAddress preferred_laddr, size_t offset, size_t size);

    virtual String absolute_path() const = 0;

    virtual const char* class_name() const = 0;

    virtual bool is_seekable() const { return false; }

    virtual bool is_device() const { return false; }
    virtual bool is_tty() const { return false; }
    virtual bool is_master_pty() const { return false; }
    virtual bool is_block_device() const { return false; }
    virtual bool is_character_device() const { return false; }

protected:
    File();
};
